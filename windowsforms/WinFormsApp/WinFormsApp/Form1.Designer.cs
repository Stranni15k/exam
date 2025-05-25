namespace WinFormsApp
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            groupBoxAddPatient = new GroupBox();
            buttonAddPatient = new Button();
            dateTimePickerDiagnosis = new DateTimePicker();
            numericUpDownWard = new NumericUpDown();
            numericUpDownAge = new NumericUpDown();
            textBoxName = new TextBox();
            labelDiagnosis = new Label();
            labelWard = new Label();
            labelAge = new Label();
            labelName = new Label();
            groupBoxLinqQueries = new GroupBox();
            buttonGroupByWard = new Button();
            buttonFilterByAge = new Button();
            numericUpDownFilterAge = new NumericUpDown();
            labelFilterAge = new Label();
            dataGridViewFiltered = new DataGridView();
            dataGridViewGrouped = new DataGridView();
            labelFiltered = new Label();
            labelGrouped = new Label();
            groupBoxAddPatient.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)numericUpDownWard).BeginInit();
            ((System.ComponentModel.ISupportInitialize)numericUpDownAge).BeginInit();
            groupBoxLinqQueries.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)numericUpDownFilterAge).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewFiltered).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewGrouped).BeginInit();
            SuspendLayout();
            // 
            // groupBoxAddPatient
            // 
            groupBoxAddPatient.Controls.Add(buttonAddPatient);
            groupBoxAddPatient.Controls.Add(dateTimePickerDiagnosis);
            groupBoxAddPatient.Controls.Add(numericUpDownWard);
            groupBoxAddPatient.Controls.Add(numericUpDownAge);
            groupBoxAddPatient.Controls.Add(textBoxName);
            groupBoxAddPatient.Controls.Add(labelDiagnosis);
            groupBoxAddPatient.Controls.Add(labelWard);
            groupBoxAddPatient.Controls.Add(labelAge);
            groupBoxAddPatient.Controls.Add(labelName);
            groupBoxAddPatient.Location = new Point(15, 15);
            groupBoxAddPatient.Name = "groupBoxAddPatient";
            groupBoxAddPatient.Size = new Size(420, 220);
            groupBoxAddPatient.TabIndex = 0;
            groupBoxAddPatient.TabStop = false;
            groupBoxAddPatient.Text = "Добавить пациента";
            // 
            // buttonAddPatient
            // 
            buttonAddPatient.Location = new Point(300, 175);
            buttonAddPatient.Name = "buttonAddPatient";
            buttonAddPatient.Size = new Size(100, 30);
            buttonAddPatient.TabIndex = 8;
            buttonAddPatient.Text = "Добавить";
            buttonAddPatient.UseVisualStyleBackColor = true;
            buttonAddPatient.Click += buttonAddPatient_Click;
            // 
            // dateTimePickerDiagnosis
            // 
            dateTimePickerDiagnosis.Location = new Point(140, 175);
            dateTimePickerDiagnosis.Name = "dateTimePickerDiagnosis";
            dateTimePickerDiagnosis.Size = new Size(150, 23);
            dateTimePickerDiagnosis.TabIndex = 7;
            // 
            // numericUpDownWard
            // 
            numericUpDownWard.Location = new Point(140, 130);
            numericUpDownWard.Maximum = new decimal(new int[] { 999, 0, 0, 0 });
            numericUpDownWard.Minimum = new decimal(new int[] { 100, 0, 0, 0 });
            numericUpDownWard.Name = "numericUpDownWard";
            numericUpDownWard.Size = new Size(180, 23);
            numericUpDownWard.TabIndex = 6;
            numericUpDownWard.Value = new decimal(new int[] { 101, 0, 0, 0 });
            // 
            // numericUpDownAge
            // 
            numericUpDownAge.Location = new Point(140, 85);
            numericUpDownAge.Maximum = new decimal(new int[] { 120, 0, 0, 0 });
            numericUpDownAge.Minimum = new decimal(new int[] { 1, 0, 0, 0 });
            numericUpDownAge.Name = "numericUpDownAge";
            numericUpDownAge.Size = new Size(180, 23);
            numericUpDownAge.TabIndex = 5;
            numericUpDownAge.Value = new decimal(new int[] { 30, 0, 0, 0 });
            // 
            // textBoxName
            // 
            textBoxName.Location = new Point(140, 40);
            textBoxName.Name = "textBoxName";
            textBoxName.Size = new Size(260, 23);
            textBoxName.TabIndex = 4;
            // 
            // labelDiagnosis
            // 
            labelDiagnosis.AutoSize = true;
            labelDiagnosis.Location = new Point(25, 180);
            labelDiagnosis.Name = "labelDiagnosis";
            labelDiagnosis.Size = new Size(87, 15);
            labelDiagnosis.TabIndex = 3;
            labelDiagnosis.Text = "Дата диагноза:";
            // 
            // labelWard
            // 
            labelWard.AutoSize = true;
            labelWard.Location = new Point(25, 135);
            labelWard.Name = "labelWard";
            labelWard.Size = new Size(49, 15);
            labelWard.TabIndex = 2;
            labelWard.Text = "Палата:";
            // 
            // labelAge
            // 
            labelAge.AutoSize = true;
            labelAge.Location = new Point(25, 90);
            labelAge.Name = "labelAge";
            labelAge.Size = new Size(53, 15);
            labelAge.TabIndex = 1;
            labelAge.Text = "Возраст:";
            // 
            // labelName
            // 
            labelName.AutoSize = true;
            labelName.Location = new Point(25, 45);
            labelName.Name = "labelName";
            labelName.Size = new Size(34, 15);
            labelName.TabIndex = 0;
            labelName.Text = "Имя:";
            // 
            // groupBoxLinqQueries
            // 
            groupBoxLinqQueries.Controls.Add(buttonGroupByWard);
            groupBoxLinqQueries.Controls.Add(buttonFilterByAge);
            groupBoxLinqQueries.Controls.Add(numericUpDownFilterAge);
            groupBoxLinqQueries.Controls.Add(labelFilterAge);
            groupBoxLinqQueries.Location = new Point(450, 15);
            groupBoxLinqQueries.Name = "groupBoxLinqQueries";
            groupBoxLinqQueries.Size = new Size(380, 220);
            groupBoxLinqQueries.TabIndex = 1;
            groupBoxLinqQueries.TabStop = false;
            groupBoxLinqQueries.Text = "LINQ Запросы";
            // 
            // buttonGroupByWard
            // 
            buttonGroupByWard.Location = new Point(25, 120);
            buttonGroupByWard.Name = "buttonGroupByWard";
            buttonGroupByWard.Size = new Size(330, 35);
            buttonGroupByWard.TabIndex = 3;
            buttonGroupByWard.Text = "Группировка по палатам (лямбда)";
            buttonGroupByWard.UseVisualStyleBackColor = true;
            buttonGroupByWard.Click += buttonGroupByWard_Click;
            // 
            // buttonFilterByAge
            // 
            buttonFilterByAge.Location = new Point(220, 40);
            buttonFilterByAge.Name = "buttonFilterByAge";
            buttonFilterByAge.Size = new Size(135, 35);
            buttonFilterByAge.TabIndex = 2;
            buttonFilterByAge.Text = "Фильтр по возрасту";
            buttonFilterByAge.UseVisualStyleBackColor = true;
            buttonFilterByAge.Click += buttonFilterByAge_Click;
            // 
            // numericUpDownFilterAge
            // 
            numericUpDownFilterAge.Location = new Point(140, 45);
            numericUpDownFilterAge.Maximum = new decimal(new int[] { 120, 0, 0, 0 });
            numericUpDownFilterAge.Name = "numericUpDownFilterAge";
            numericUpDownFilterAge.Size = new Size(70, 23);
            numericUpDownFilterAge.TabIndex = 1;
            numericUpDownFilterAge.Value = new decimal(new int[] { 40, 0, 0, 0 });
            // 
            // labelFilterAge
            // 
            labelFilterAge.AutoSize = true;
            labelFilterAge.Location = new Point(25, 50);
            labelFilterAge.Name = "labelFilterAge";
            labelFilterAge.Size = new Size(97, 15);
            labelFilterAge.TabIndex = 0;
            labelFilterAge.Text = "Возраст старше:";
            // 
            // dataGridViewFiltered
            // 
            dataGridViewFiltered.AllowUserToAddRows = false;
            dataGridViewFiltered.AllowUserToDeleteRows = false;
            dataGridViewFiltered.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewFiltered.Location = new Point(15, 285);
            dataGridViewFiltered.Name = "dataGridViewFiltered";
            dataGridViewFiltered.ReadOnly = true;
            dataGridViewFiltered.Size = new Size(815, 170);
            dataGridViewFiltered.TabIndex = 2;
            // 
            // dataGridViewGrouped
            // 
            dataGridViewGrouped.AllowUserToAddRows = false;
            dataGridViewGrouped.AllowUserToDeleteRows = false;
            dataGridViewGrouped.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewGrouped.Location = new Point(15, 490);
            dataGridViewGrouped.Name = "dataGridViewGrouped";
            dataGridViewGrouped.ReadOnly = true;
            dataGridViewGrouped.Size = new Size(815, 140);
            dataGridViewGrouped.TabIndex = 3;
            // 
            // labelFiltered
            // 
            labelFiltered.AutoSize = true;
            labelFiltered.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point);
            labelFiltered.Location = new Point(15, 260);
            labelFiltered.Name = "labelFiltered";
            labelFiltered.Size = new Size(231, 15);
            labelFiltered.TabIndex = 4;
            labelFiltered.Text = "Пациенты старше указанного возраста";
            // 
            // labelGrouped
            // 
            labelGrouped.AutoSize = true;
            labelGrouped.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point);
            labelGrouped.Location = new Point(15, 465);
            labelGrouped.Name = "labelGrouped";
            labelGrouped.Size = new Size(147, 15);
            labelGrouped.TabIndex = 5;
            labelGrouped.Text = "Группировка по палатам";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(850, 650);
            Controls.Add(labelGrouped);
            Controls.Add(labelFiltered);
            Controls.Add(dataGridViewGrouped);
            Controls.Add(dataGridViewFiltered);
            Controls.Add(groupBoxLinqQueries);
            Controls.Add(groupBoxAddPatient);
            Name = "Form1";
            Text = "Управление пациентами";
            groupBoxAddPatient.ResumeLayout(false);
            groupBoxAddPatient.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)numericUpDownWard).EndInit();
            ((System.ComponentModel.ISupportInitialize)numericUpDownAge).EndInit();
            groupBoxLinqQueries.ResumeLayout(false);
            groupBoxLinqQueries.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)numericUpDownFilterAge).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewFiltered).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewGrouped).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private GroupBox groupBoxAddPatient;
        private Button buttonAddPatient;
        private DateTimePicker dateTimePickerDiagnosis;
        private NumericUpDown numericUpDownWard;
        private NumericUpDown numericUpDownAge;
        private TextBox textBoxName;
        private Label labelDiagnosis;
        private Label labelWard;
        private Label labelAge;
        private Label labelName;
        private GroupBox groupBoxLinqQueries;
        private Button buttonGroupByWard;
        private Button buttonFilterByAge;
        private NumericUpDown numericUpDownFilterAge;
        private Label labelFilterAge;
        private DataGridView dataGridViewFiltered;
        private DataGridView dataGridViewGrouped;
        private Label labelFiltered;
        private Label labelGrouped;
    }
}
