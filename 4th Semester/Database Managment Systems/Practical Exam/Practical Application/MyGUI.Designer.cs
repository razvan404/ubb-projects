namespace Practical
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
            this.parentTable = new System.Windows.Forms.DataGridView();
            this.parentTableLabel = new System.Windows.Forms.Label();
            this.childTable = new System.Windows.Forms.DataGridView();
            this.childTableLabel = new System.Windows.Forms.Label();
            this.selectedTextLabel = new System.Windows.Forms.Label();
            this.selectedLabel = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textLabel1 = new System.Windows.Forms.Label();
            this.textLabel2 = new System.Windows.Forms.Label();
            this.insertButton = new System.Windows.Forms.Button();
            this.deleteButton = new System.Windows.Forms.Button();
            this.updateButton = new System.Windows.Forms.Button();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textLabel3 = new System.Windows.Forms.Label();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textLabel4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.parentTable)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.childTable)).BeginInit();
            this.SuspendLayout();
            // 
            // parentTable
            // 
            this.parentTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.parentTable.Location = new System.Drawing.Point(12, 36);
            this.parentTable.Name = "parentTable";
            this.parentTable.Size = new System.Drawing.Size(352, 472);
            this.parentTable.TabIndex = 0;
            this.parentTable.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.parentTable_CellClick);
            // 
            // parentTableLabel
            // 
            this.parentTableLabel.AutoSize = true;
            this.parentTableLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.parentTableLabel.Location = new System.Drawing.Point(125, 9);
            this.parentTableLabel.Name = "parentTableLabel";
            this.parentTableLabel.Size = new System.Drawing.Size(117, 24);
            this.parentTableLabel.TabIndex = 1;
            this.parentTableLabel.Text = "Parent Table";
            // 
            // childTable
            // 
            this.childTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.childTable.Location = new System.Drawing.Point(397, 226);
            this.childTable.Name = "childTable";
            this.childTable.Size = new System.Drawing.Size(530, 255);
            this.childTable.TabIndex = 2;
            this.childTable.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.childTable_CellClick);
            // 
            // childTableLabel
            // 
            this.childTableLabel.AutoSize = true;
            this.childTableLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F);
            this.childTableLabel.Location = new System.Drawing.Point(606, 484);
            this.childTableLabel.Name = "childTableLabel";
            this.childTableLabel.Size = new System.Drawing.Size(106, 24);
            this.childTableLabel.TabIndex = 3;
            this.childTableLabel.Text = "Child Table";
            // 
            // selectedTextLabel
            // 
            this.selectedTextLabel.AutoSize = true;
            this.selectedTextLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.selectedTextLabel.Location = new System.Drawing.Point(409, 36);
            this.selectedTextLabel.Name = "selectedTextLabel";
            this.selectedTextLabel.Size = new System.Drawing.Size(76, 20);
            this.selectedTextLabel.TabIndex = 4;
            this.selectedTextLabel.Text = "Selected:";
            // 
            // selectedLabel
            // 
            this.selectedLabel.AutoSize = true;
            this.selectedLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.selectedLabel.Location = new System.Drawing.Point(553, 36);
            this.selectedLabel.Name = "selectedLabel";
            this.selectedLabel.Size = new System.Drawing.Size(14, 20);
            this.selectedLabel.TabIndex = 5;
            this.selectedLabel.Text = "-";
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.textBox1.Location = new System.Drawing.Point(549, 59);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(378, 26);
            this.textBox1.TabIndex = 6;
            // 
            // textBox2
            // 
            this.textBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.textBox2.Location = new System.Drawing.Point(549, 91);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(378, 26);
            this.textBox2.TabIndex = 7;
            // 
            // textLabel1
            // 
            this.textLabel1.AutoSize = true;
            this.textLabel1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.textLabel1.Location = new System.Drawing.Point(409, 62);
            this.textLabel1.Name = "textLabel1";
            this.textLabel1.Size = new System.Drawing.Size(82, 20);
            this.textLabel1.TabIndex = 8;
            this.textLabel1.Text = "Denumire:";
            // 
            // textLabel2
            // 
            this.textLabel2.AutoSize = true;
            this.textLabel2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.textLabel2.Location = new System.Drawing.Point(409, 94);
            this.textLabel2.Name = "textLabel2";
            this.textLabel2.Size = new System.Drawing.Size(86, 20);
            this.textLabel2.TabIndex = 9;
            this.textLabel2.Text = "An Pictura:";
            // 
            // insertButton
            // 
            this.insertButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.insertButton.Location = new System.Drawing.Point(397, 188);
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
            this.deleteButton.Location = new System.Drawing.Point(759, 188);
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
            this.updateButton.Location = new System.Drawing.Point(573, 188);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(180, 32);
            this.updateButton.TabIndex = 13;
            this.updateButton.Text = "Update";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // textBox3
            // 
            this.textBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.textBox3.Location = new System.Drawing.Point(549, 123);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(378, 26);
            this.textBox3.TabIndex = 14;
            // 
            // textLabel3
            // 
            this.textLabel3.AutoSize = true;
            this.textLabel3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.textLabel3.Location = new System.Drawing.Point(409, 126);
            this.textLabel3.Name = "textLabel3";
            this.textLabel3.Size = new System.Drawing.Size(97, 20);
            this.textLabel3.TabIndex = 15;
            this.textLabel3.Text = "Dimensiune:";
            // 
            // textBox4
            // 
            this.textBox4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.textBox4.Location = new System.Drawing.Point(549, 156);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(378, 26);
            this.textBox4.TabIndex = 16;
            // 
            // textLabel4
            // 
            this.textLabel4.AutoSize = true;
            this.textLabel4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.textLabel4.Location = new System.Drawing.Point(409, 159);
            this.textLabel4.Name = "textLabel4";
            this.textLabel4.Size = new System.Drawing.Size(82, 20);
            this.textLabel4.TabIndex = 17;
            this.textLabel4.Text = "ID Muzeu:";
            // 
            // MyGUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(950, 520);
            this.Controls.Add(this.textLabel4);
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.textLabel3);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.insertButton);
            this.Controls.Add(this.textLabel2);
            this.Controls.Add(this.textLabel1);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.selectedLabel);
            this.Controls.Add(this.selectedTextLabel);
            this.Controls.Add(this.childTableLabel);
            this.Controls.Add(this.childTable);
            this.Controls.Add(this.parentTableLabel);
            this.Controls.Add(this.parentTable);
            this.Name = "MyGUI";
            this.Text = "MyGUI";
            ((System.ComponentModel.ISupportInitialize)(this.parentTable)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.childTable)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView parentTable;
        private System.Windows.Forms.Label parentTableLabel;
        private System.Windows.Forms.DataGridView childTable;
        private System.Windows.Forms.Label childTableLabel;
        private System.Windows.Forms.Label selectedTextLabel;
        private System.Windows.Forms.Label selectedLabel;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label textLabel1;
        private System.Windows.Forms.Label textLabel2;
        private System.Windows.Forms.Button insertButton;
        private System.Windows.Forms.Button deleteButton;
        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Label textLabel3;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.Label textLabel4;
    }
}

