// Migration файл - демонстрация структуры данных для задания
// В реальном проекте это был бы файл миграции базы данных

namespace WinFormsApp.Migrations
{
    public static class Migration_CreatePatients
    {
        public static string GetCreateTableSQL()
        {
            return @"
                CREATE TABLE Patients (
                    Id INT PRIMARY KEY IDENTITY(1,1),
                    Name NVARCHAR(100) NOT NULL,
                    Age INT NOT NULL,
                    Ward INT NOT NULL,
                    DiagnosisDate DATETIME NOT NULL
                );
                
                INSERT INTO Patients (Name, Age, Ward, DiagnosisDate) VALUES
                ('Иванов И.И.', 45, 101, '2024-01-15'),
                ('Петров П.П.', 32, 102, '2024-01-16'),
                ('Сидоров С.С.', 67, 101, '2024-01-17');
            ";
        }
    }
} 