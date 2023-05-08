namespace Contests
{
    partial class MyGUI
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.coordinatorsTable = new System.Windows.Forms.DataGridView();
            this.coordinatorsTableLabel = new System.Windows.Forms.Label();
            this.studentsTable = new System.Windows.Forms.DataGridView();
            this.studentsTableLabel = new System.Windows.Forms.Label();
            this.selectedCoordinatorTextLabel = new System.Windows.Forms.Label();
            this.selectedCoordinatorLabel = new System.Windows.Forms.Label();
            this.studentNameTextBox = new System.Windows.Forms.TextBox();
            this.studentSchoolTextBox = new System.Windows.Forms.TextBox();
            this.studentNameLabel = new System.Windows.Forms.Label();
            this.studentSchoolLabel = new System.Windows.Forms.Label();
            this.insertButton = new System.Windows.Forms.Button();
            this.deleteButton = new System.Windows.Forms.Button();
            this.updateButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.coordinatorsTable)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.studentsTable)).BeginInit();
            this.SuspendLayout();
            // 
            // coordinatorsTable
            // 
            this.coordinatorsTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.coordinatorsTable.Location = new System.Drawing.Point(12, 36);
            this.coordinatorsTable.Name = "coordinatorsTable";
            this.coordinatorsTable.Size = new System.Drawing.Size(352, 378);
            this.coordinatorsTable.TabIndex = 0;
            this.coordinatorsTable.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.parentTable_CellClick);
            // 
            // coordinatorsTableLabel
            // 
            this.coordinatorsTableLabel.AutoSize = true;
            this.coordinatorsTableLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.coordinatorsTableLabel.Location = new System.Drawing.Point(103, 9);
            this.coordinatorsTableLabel.Name = "coordinatorsTableLabel";
            this.coordinatorsTableLabel.Size = new System.Drawing.Size(170, 24);
            this.coordinatorsTableLabel.TabIndex = 1;
            this.coordinatorsTableLabel.Text = "Coordinators Table";
            // 
            // studentsTable
            // 
            this.studentsTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.studentsTable.Location = new System.Drawing.Point(397, 161);
            this.studentsTable.Name = "studentsTable";
            this.studentsTable.Size = new System.Drawing.Size(530, 224);
            this.studentsTable.TabIndex = 2;
            this.studentsTable.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.childTable_CellClick);
            // 
            // studentsTableLabel
            // 
            this.studentsTableLabel.AutoSize = true;
            this.studentsTableLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.studentsTableLabel.Location = new System.Drawing.Point(596, 390);
            this.studentsTableLabel.Name = "studentsTableLabel";
            this.studentsTableLabel.Size = new System.Drawing.Size(136, 24);
            this.studentsTableLabel.TabIndex = 3;
            this.studentsTableLabel.Text = "Students Table";
            // 
            // selectedCoordinatorTextLabel
            // 
            this.selectedCoordinatorTextLabel.AutoSize = true;
            this.selectedCoordinatorTextLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.selectedCoordinatorTextLabel.Location = new System.Drawing.Point(409, 36);
            this.selectedCoordinatorTextLabel.Name = "selectedCoordinatorTextLabel";
            this.selectedCoordinatorTextLabel.Size = new System.Drawing.Size(163, 20);
            this.selectedCoordinatorTextLabel.TabIndex = 4;
            this.selectedCoordinatorTextLabel.Text = "Selected Coordinator:";
            // 
            // selectedCoordinatorLabel
            // 
            this.selectedCoordinatorLabel.AutoSize = true;
            this.selectedCoordinatorLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.selectedCoordinatorLabel.Location = new System.Drawing.Point(569, 36);
            this.selectedCoordinatorLabel.Name = "selectedCoordinatorLabel";
            this.selectedCoordinatorLabel.Size = new System.Drawing.Size(14, 20);
            this.selectedCoordinatorLabel.TabIndex = 5;
            this.selectedCoordinatorLabel.Text = "-";
            // 
            // studentNameTextBox
            // 
            this.studentNameTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.studentNameTextBox.Location = new System.Drawing.Point(549, 59);
            this.studentNameTextBox.Name = "studentNameTextBox";
            this.studentNameTextBox.Size = new System.Drawing.Size(378, 26);
            this.studentNameTextBox.TabIndex = 6;
            // 
            // studentSchoolTextBox
            // 
            this.studentSchoolTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.studentSchoolTextBox.Location = new System.Drawing.Point(549, 91);
            this.studentSchoolTextBox.Name = "studentSchoolTextBox";
            this.studentSchoolTextBox.Size = new System.Drawing.Size(378, 26);
            this.studentSchoolTextBox.TabIndex = 7;
            // 
            // studentNameLabel
            // 
            this.studentNameLabel.AutoSize = true;
            this.studentNameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.studentNameLabel.Location = new System.Drawing.Point(409, 62);
            this.studentNameLabel.Name = "studentNameLabel";
            this.studentNameLabel.Size = new System.Drawing.Size(127, 20);
            this.studentNameLabel.TabIndex = 8;
            this.studentNameLabel.Text = "Student\'s Name:";
            // 
            // studentSchoolLabel
            // 
            this.studentSchoolLabel.AutoSize = true;
            this.studentSchoolLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.studentSchoolLabel.Location = new System.Drawing.Point(409, 94);
            this.studentSchoolLabel.Name = "studentSchoolLabel";
            this.studentSchoolLabel.Size = new System.Drawing.Size(134, 20);
            this.studentSchoolLabel.TabIndex = 9;
            this.studentSchoolLabel.Text = "Student\'s School:";
            // 
            // insertButton
            // 
            this.insertButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.insertButton.Location = new System.Drawing.Point(397, 123);
            this.insertButton.Name = "insertButton";
            this.insertButton.Size = new System.Drawing.Size(170, 32);
            this.insertButton.TabIndex = 10;
            this.insertButton.Text = "Insert";
            this.insertButton.UseVisualStyleBackColor = true;
            this.insertButton.Click += new System.EventHandler(this.insertButton_Click);
            // 
            // deleteButton
            // 
            this.deleteButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.deleteButton.Location = new System.Drawing.Point(759, 123);
            this.deleteButton.Name = "deleteButton";
            this.deleteButton.Size = new System.Drawing.Size(168, 32);
            this.deleteButton.TabIndex = 12;
            this.deleteButton.Text = "Delete";
            this.deleteButton.UseVisualStyleBackColor = true;
            this.deleteButton.Click += new System.EventHandler(this.deleteButton_Click);
            // 
            // updateButton
            // 
            this.updateButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.updateButton.Location = new System.Drawing.Point(573, 123);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(180, 32);
            this.updateButton.TabIndex = 13;
            this.updateButton.Text = "Update";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // MyGUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(950, 429);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.insertButton);
            this.Controls.Add(this.studentSchoolLabel);
            this.Controls.Add(this.studentNameLabel);
            this.Controls.Add(this.studentSchoolTextBox);
            this.Controls.Add(this.studentNameTextBox);
            this.Controls.Add(this.selectedCoordinatorLabel);
            this.Controls.Add(this.selectedCoordinatorTextLabel);
            this.Controls.Add(this.studentsTableLabel);
            this.Controls.Add(this.studentsTable);
            this.Controls.Add(this.coordinatorsTableLabel);
            this.Controls.Add(this.coordinatorsTable);
            this.Name = "MyGUI";
            this.Text = "MyGUI";
            ((System.ComponentModel.ISupportInitialize)(this.coordinatorsTable)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.studentsTable)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView coordinatorsTable;
        private System.Windows.Forms.Label coordinatorsTableLabel;
        private System.Windows.Forms.DataGridView studentsTable;
        private System.Windows.Forms.Label studentsTableLabel;
        private System.Windows.Forms.Label selectedCoordinatorTextLabel;
        private System.Windows.Forms.Label selectedCoordinatorLabel;
        private System.Windows.Forms.TextBox studentNameTextBox;
        private System.Windows.Forms.TextBox studentSchoolTextBox;
        private System.Windows.Forms.Label studentNameLabel;
        private System.Windows.Forms.Label studentSchoolLabel;
        private System.Windows.Forms.Button insertButton;
        private System.Windows.Forms.Button deleteButton;
        private System.Windows.Forms.Button updateButton;
    }
}

