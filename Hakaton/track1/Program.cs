using Microsoft.VisualBasic.FileIO;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

public class CsvImporter
{
    public static List<Dictionary<string, string>> ImportCsv(string filePath, char delimiter = ',', bool hasHeader = true)
    {
        List<Dictionary<string, string>> data = new List<Dictionary<string, string>>();

        try
        {
            using (TextFieldParser parser = new TextFieldParser(filePath))
            {
                parser.TextFieldType = FieldType.Delimited;
                parser.SetDelimiters(delimiter.ToString());

                if (hasHeader)
                {
                    string[] header = parser.ReadFields();

                    if (header == null || header.Length == 0)
                    {
                        throw new InvalidDataException("CSV-файл не содержит заголовки.");
                    }

                    Dictionary<string, string> existingFirstAttributes = new Dictionary<string, string>();


                    while (!parser.EndOfData)
                    {
                        string[] fields = parser.ReadFields();

                        if (fields.Length != header.Length)
                        {
                            Console.WriteLine($"Несоответствие количества полей в строке и заголовке. Строка пропущена.");
                            continue;
                        }

                        Dictionary<string, string> row = new Dictionary<string, string>();
                        for (int i = 0; i < header.Length; i++)
                        {
                            row.Add(header[i], fields[i]);
                        }

                        //Проверка
                        if (row.Count > 0)
                        {

                            DateTime createDate;
                            DateTime updateDate;

                            //Неверный формат
                            if (!DateTime.TryParse(row["create_date"], out createDate) || !DateTime.TryParse(row["update_date"], out updateDate))
                            {
                                Console.WriteLine("Строка пропущена: неверный формат даты в полях 'create_date' или 'update_date'.");
                                continue;
                            }

                            //Дата создания больше даты обновления
                            if (updateDate < createDate)
                            {
                                Console.WriteLine("Строка пропущена: дата обновления раньше даты создания.");
                                continue;
                            }

                            //Дата создания или обновления больше тек. даты
                            if (updateDate > DateTime.Now || createDate > DateTime.Now)
                            {
                                Console.WriteLine("Строка пропущена: дата обновления или создания больше текущей даты.");
                                continue;
                            }


                            string key = row.First().Key;
                            string value = row.First().Value;

                            if (!existingFirstAttributes.ContainsKey(key) || existingFirstAttributes[key] != value)
                            {
                                data.Add(row);
                                existingFirstAttributes[key] = value;
                            }
                        }
                    }

                    // Сортировка по дате обновления (в порядке убывания)
                    data.Sort((x, y) => DateTime.Parse(y["update_date"]).CompareTo(DateTime.Parse(x["update_date"])));
                }
                else
                {
                    while (!parser.EndOfData)
                    {
                        string[] fields = parser.ReadFields();

                        if (fields == null || fields.Length == 0) continue;

                        Dictionary<string, string> row = new Dictionary<string, string>();
                        for (int i = 0; i < fields.Length; i++)
                        {
                            row.Add($"Column{i + 1}", fields[i]);
                        }
                        data.Add(row);
                    }
                }
            }
            return data;
        }
        catch (FileNotFoundException)
        {
            Console.WriteLine($"Файл {filePath} не найден.");
            return null;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при импорте CSV: {ex.Message}");
            return null;
        }
    }

    public static void Main()
    {
        string filePath = "ds_dirty_fin_202410041147.csv";
        char delimiter = ',';

        List<Dictionary<string, string>> data = CsvImporter.ImportCsv(filePath, delimiter, true);

        if (data != null)
        {
            foreach (var row in data)
            {
                // Не вариант (попытка вывода)
                foreach (var keyValuePair in row)
                {
                    Console.Write($"{keyValuePair.Key}: {keyValuePair.Value}, ");
                }
                Console.WriteLine();
            }
        }
    }
}