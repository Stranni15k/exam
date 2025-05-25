using System.Xml.Serialization;

namespace WinFormsApp
{
    public partial class Form1 : Form
    {
        private List<Patient> patients;
        private readonly string filePath = "patients.xml";

        public Form1()
        {
            InitializeComponent();
            patients = new List<Patient>();
            LoadPatientsFromFile();
        }

        private void buttonAddPatient_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxName.Text))
            {
                MessageBox.Show("Введите имя пациента!");
                return;
            }

            var patient = new Patient(
                textBoxName.Text,
                (int)numericUpDownAge.Value,
                (int)numericUpDownWard.Value,
                dateTimePickerDiagnosis.Value
            );

            patients.Add(patient);
            SavePatientsToFile();
            MessageBox.Show("Пациент добавлен успешно!");
            
            // Очищаем поля
            textBoxName.Text = "";
            numericUpDownAge.Value = 30;
            numericUpDownWard.Value = 101;
            dateTimePickerDiagnosis.Value = DateTime.Now;
        }

        private void buttonFilterByAge_Click(object sender, EventArgs e)
        {
            int minAge = (int)numericUpDownFilterAge.Value;

            // Классический LINQ запрос
            var filteredPatients = from patient in patients
                                 where patient.Age > minAge
                                 orderby patient.Age descending
                                 select new
                                 {
                                     Имя = patient.Name,
                                     Возраст = patient.Age,
                                     Палата = patient.Ward,
                                     ДатаДиагноза = patient.DiagnosisDate.ToShortDateString()
                                 };

            dataGridViewFiltered.DataSource = filteredPatients.ToList();
        }

        private void buttonGroupByWard_Click(object sender, EventArgs e)
        {
            // LINQ запрос через методы (лямбда-выражения)
            var wardGroups = patients
                .GroupBy(p => p.Ward)
                .Select(g => new
                {
                    Палата = g.Key,
                    КоличествоПациентов = g.Count(),
                    Пациенты = string.Join(", ", g.Select(p => p.Name))
                })
                .OrderByDescending(g => g.КоличествоПациентов)
                .ToList();

            dataGridViewGrouped.DataSource = wardGroups;

            // Настраиваем отображение для корректного показа всех пациентов
            if (dataGridViewGrouped.Columns.Count > 0)
            {
                dataGridViewGrouped.Columns["Палата"].Width = 80;
                dataGridViewGrouped.Columns["КоличествоПациентов"].Width = 120;
                dataGridViewGrouped.Columns["Пациенты"].Width = 560;
                
                // Включаем перенос строк для колонки с пациентами
                dataGridViewGrouped.Columns["Пациенты"].DefaultCellStyle.WrapMode = DataGridViewTriState.True;
                
                // Автоподбор высоты строк
                dataGridViewGrouped.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCells;
            }

            // Выводим палату с наибольшим количеством пациентов
            if (wardGroups.Count > 0)
            {
                var maxWard = wardGroups.First();
                MessageBox.Show($"Палата с наибольшим количеством пациентов: №{maxWard.Палата} ({maxWard.КоличествоПациентов} пациентов)");
            }
        }

        private void SavePatientsToFile()
        {
            try
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Patient>));
                using (FileStream fs = new FileStream(filePath, FileMode.Create))
                {
                    serializer.Serialize(fs, patients);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка сохранения: {ex.Message}");
            }
        }

        private void LoadPatientsFromFile()
        {
            if (!File.Exists(filePath))
            {
                // Создаем тестовые данные если файл не существует
                CreateDefaultPatients();
                return;
            }

            try
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Patient>));
                using (FileStream fs = new FileStream(filePath, FileMode.Open))
                {
                    var deserializedPatients = (List<Patient>?)serializer.Deserialize(fs);
                    patients = deserializedPatients ?? new List<Patient>();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка загрузки: {ex.Message}");
                CreateDefaultPatients();
            }
        }

        private void CreateDefaultPatients()
        {
            patients = new List<Patient>
            {
                new Patient("Иванов Иван Иванович", 45, 101, DateTime.Now.AddDays(-5)),
                new Patient("Петров Петр Петрович", 32, 102, DateTime.Now.AddDays(-3)),
                new Patient("Сидоров Сидор Сидорович", 67, 101, DateTime.Now.AddDays(-7)),
                new Patient("Козлова Анна Владимировна", 28, 103, DateTime.Now.AddDays(-2)),
                new Patient("Морозов Николай Алексеевич", 55, 102, DateTime.Now.AddDays(-4)),
                new Patient("Власова Елена Игоревна", 39, 101, DateTime.Now.AddDays(-1))
            };
            SavePatientsToFile();
        }
    }
}
