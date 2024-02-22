using System;
namespace _253501_Maliush_Lab._4;

public class FileService : IFileService<Art>
{
    public IEnumerable<Art> ReadFile(string fileName)
    {
        using (FileStream stream = new(fileName, FileMode.Open))
        {
            using (BinaryReader reader = new(stream))
            {
                while (reader.BaseStream.Position != reader.BaseStream.Length)
                {
                    Art newArt = null;
                    try
                    {
                        newArt = new(reader.ReadString(), reader.ReadInt32(), reader.ReadBoolean());
                    }
                    catch (EndOfStreamException)
                    {
                        Console.WriteLine("Error: We've reached the end of the file");
                        break;
                    }
                    catch (IOException)
                    {
                        Console.WriteLine("Error: Error of Input-Output");
                        break;
                    }
                    catch (ArgumentOutOfRangeException)
                    {
                        Console.WriteLine("Error: Argument out of Range");
                        break;
                    }
                    catch (ObjectDisposedException)
                    {
                        Console.WriteLine("Error: Object was deleted");
                        break;
                    }
                    catch (NotSupportedException)
                    {
                        Console.WriteLine("Error: operation doesn't supported.");
                        break;
                    }

                    if (newArt != null) yield return newArt;
                }
            }
        }
    }

    public void SaveData(IEnumerable<Art> data, string fileName)
    {
        using FileStream stream = new(fileName, FileMode.Create);

        using BinaryWriter writer = new(stream);
            
                foreach (Art i in data)
                {
                    try
                    {
                        //writer.Write($"{i.GetName()}{i.GetYearOfCreating()}{i.GetIsItHas()}");
                        writer.Write(i.Name);
                        writer.Write(i.GetYearOfCreating());
                        writer.Write(i.GetIsItHas());
                    }
                    catch (EndOfStreamException)
                    {
                        Console.WriteLine("Error: We've reached the end of the file");
                        break;
                    }
                    catch (IOException)
                    {
                        Console.WriteLine("Error: Error of Input-Output");
                        break;
                    }
                    catch (ArgumentOutOfRangeException)
                    {
                        Console.WriteLine("Error: Argument out of Range");
                        break;
                    }
                    catch (ObjectDisposedException)
                    {
                        Console.WriteLine("Error: Object was deleted");
                        break;
                    }
                    catch (NotSupportedException)
                    {
                        Console.WriteLine("Error: operation doesn't supported.");
                        break;
                    }
                }
            
        
    }
}

