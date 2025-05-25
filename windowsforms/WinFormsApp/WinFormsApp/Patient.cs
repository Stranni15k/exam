using System.Xml.Serialization;

namespace WinFormsApp
{
    [Serializable]
    public class Patient
    {
        public string Name { get; set; } = string.Empty;
        public int Age { get; set; }
        public int Ward { get; set; }
        public DateTime DiagnosisDate { get; set; }

        public Patient() { }

        public Patient(string name, int age, int ward, DateTime diagnosisDate)
        {
            Name = name;
            Age = age;
            Ward = ward;
            DiagnosisDate = diagnosisDate;
        }

        public override string ToString()
        {
            return $"{Name}, {Age} лет, палата {Ward}, диагноз от {DiagnosisDate.ToShortDateString()}";
        }
    }
} 