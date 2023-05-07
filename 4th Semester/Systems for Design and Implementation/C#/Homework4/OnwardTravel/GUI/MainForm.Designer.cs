namespace OnwardTravel.GUI
{
    partial class MainForm
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
            this.welcomeLabel = new System.Windows.Forms.Label();
            this.logOutButton = new System.Windows.Forms.Button();
            this.ridesTable = new System.Windows.Forms.DataGridView();
            this.ridesListLabel = new System.Windows.Forms.Label();
            this.destinationTextBox = new System.Windows.Forms.TextBox();
            this.destinationLabel = new System.Windows.Forms.Label();
            this.departureDateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.departureLabel = new System.Windows.Forms.Label();
            this.searchRideButton = new System.Windows.Forms.Button();
            this.clearFiltersButton = new System.Windows.Forms.Button();
            this.clientsTable = new System.Windows.Forms.DataGridView();
            this.clientsTableLabel = new System.Windows.Forms.Label();
            this.clientNameTextBox = new System.Windows.Forms.TextBox();
            this.clientNameLabel = new System.Windows.Forms.Label();
            this.clientPhoneLabel = new System.Windows.Forms.Label();
            this.noSeatsLabel = new System.Windows.Forms.Label();
            this.clientPhoneTextBox = new System.Windows.Forms.TextBox();
            this.noSeatsTextBox = new System.Windows.Forms.TextBox();
            this.reserveButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.ridesTable)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.clientsTable)).BeginInit();
            this.SuspendLayout();
            // 
            // welcomeLabel
            // 
            this.welcomeLabel.AutoSize = true;
            this.welcomeLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.welcomeLabel.Location = new System.Drawing.Point(12, 16);
            this.welcomeLabel.Name = "welcomeLabel";
            this.welcomeLabel.Size = new System.Drawing.Size(118, 20);
            this.welcomeLabel.TabIndex = 0;
            this.welcomeLabel.Text = "Welcome, user!";
            // 
            // logOutButton
            // 
            this.logOutButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            this.logOutButton.Location = new System.Drawing.Point(700, 9);
            this.logOutButton.Name = "logOutButton";
            this.logOutButton.Size = new System.Drawing.Size(88, 36);
            this.logOutButton.TabIndex = 1;
            this.logOutButton.Text = "log out";
            this.logOutButton.UseVisualStyleBackColor = true;
            this.logOutButton.Click += new System.EventHandler(this.logOutButton_Click);
            // 
            // ridesTable
            // 
            this.ridesTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ridesTable.Location = new System.Drawing.Point(12, 82);
            this.ridesTable.Name = "ridesTable";
            this.ridesTable.Size = new System.Drawing.Size(339, 228);
            this.ridesTable.TabIndex = 2;
            this.ridesTable.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.ridesTable_CellClick);
            // 
            // ridesListLabel
            // 
            this.ridesListLabel.AutoSize = true;
            this.ridesListLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.ridesListLabel.Location = new System.Drawing.Point(12, 62);
            this.ridesListLabel.Name = "ridesListLabel";
            this.ridesListLabel.Size = new System.Drawing.Size(70, 17);
            this.ridesListLabel.TabIndex = 3;
            this.ridesListLabel.Text = "Rides List";
            // 
            // destinationTextBox
            // 
            this.destinationTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.destinationTextBox.Location = new System.Drawing.Point(101, 316);
            this.destinationTextBox.Name = "destinationTextBox";
            this.destinationTextBox.Size = new System.Drawing.Size(250, 23);
            this.destinationTextBox.TabIndex = 4;
            // 
            // destinationLabel
            // 
            this.destinationLabel.AutoSize = true;
            this.destinationLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.destinationLabel.Location = new System.Drawing.Point(12, 322);
            this.destinationLabel.Name = "destinationLabel";
            this.destinationLabel.Size = new System.Drawing.Size(83, 17);
            this.destinationLabel.TabIndex = 5;
            this.destinationLabel.Text = "Destination:";
            // 
            // departureDateTimePicker
            // 
            this.departureDateTimePicker.CalendarFont = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.departureDateTimePicker.Location = new System.Drawing.Point(101, 345);
            this.departureDateTimePicker.Name = "departureDateTimePicker";
            this.departureDateTimePicker.Size = new System.Drawing.Size(250, 20);
            this.departureDateTimePicker.TabIndex = 6;
            // 
            // departureLabel
            // 
            this.departureLabel.AutoSize = true;
            this.departureLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.departureLabel.Location = new System.Drawing.Point(19, 348);
            this.departureLabel.Name = "departureLabel";
            this.departureLabel.Size = new System.Drawing.Size(76, 17);
            this.departureLabel.TabIndex = 7;
            this.departureLabel.Text = "Departure:";
            // 
            // searchRideButton
            // 
            this.searchRideButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.searchRideButton.Location = new System.Drawing.Point(12, 371);
            this.searchRideButton.Name = "searchRideButton";
            this.searchRideButton.Size = new System.Drawing.Size(339, 33);
            this.searchRideButton.TabIndex = 8;
            this.searchRideButton.Text = "Search Ride";
            this.searchRideButton.UseVisualStyleBackColor = true;
            this.searchRideButton.Click += new System.EventHandler(this.searchRideButton_Click);
            // 
            // clearFiltersButton
            // 
            this.clearFiltersButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.clearFiltersButton.Location = new System.Drawing.Point(12, 410);
            this.clearFiltersButton.Name = "clearFiltersButton";
            this.clearFiltersButton.Size = new System.Drawing.Size(339, 33);
            this.clearFiltersButton.TabIndex = 9;
            this.clearFiltersButton.Text = "Clear Filters";
            this.clearFiltersButton.UseVisualStyleBackColor = true;
            this.clearFiltersButton.Click += new System.EventHandler(this.clearFiltersButton_Click);
            // 
            // clientsTable
            // 
            this.clientsTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.clientsTable.Location = new System.Drawing.Point(409, 82);
            this.clientsTable.Name = "clientsTable";
            this.clientsTable.Size = new System.Drawing.Size(379, 228);
            this.clientsTable.TabIndex = 10;
            // 
            // clientsTableLabel
            // 
            this.clientsTableLabel.AutoSize = true;
            this.clientsTableLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.clientsTableLabel.Location = new System.Drawing.Point(575, 62);
            this.clientsTableLabel.Name = "clientsTableLabel";
            this.clientsTableLabel.Size = new System.Drawing.Size(213, 17);
            this.clientsTableLabel.TabIndex = 11;
            this.clientsTableLabel.Text = "Clients List for the Selected Ride";
            // 
            // clientNameTextBox
            // 
            this.clientNameTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.clientNameTextBox.Location = new System.Drawing.Point(505, 316);
            this.clientNameTextBox.Name = "clientNameTextBox";
            this.clientNameTextBox.Size = new System.Drawing.Size(283, 23);
            this.clientNameTextBox.TabIndex = 12;
            // 
            // clientNameLabel
            // 
            this.clientNameLabel.AutoSize = true;
            this.clientNameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.clientNameLabel.Location = new System.Drawing.Point(411, 319);
            this.clientNameLabel.Name = "clientNameLabel";
            this.clientNameLabel.Size = new System.Drawing.Size(96, 17);
            this.clientNameLabel.TabIndex = 13;
            this.clientNameLabel.Text = "Client\'s name:";
            // 
            // clientPhoneLabel
            // 
            this.clientPhoneLabel.AutoSize = true;
            this.clientPhoneLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.clientPhoneLabel.Location = new System.Drawing.Point(406, 349);
            this.clientPhoneLabel.Name = "clientPhoneLabel";
            this.clientPhoneLabel.Size = new System.Drawing.Size(101, 17);
            this.clientPhoneLabel.TabIndex = 14;
            this.clientPhoneLabel.Text = "Client\'s phone:";
            // 
            // noSeatsLabel
            // 
            this.noSeatsLabel.AutoSize = true;
            this.noSeatsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.noSeatsLabel.Location = new System.Drawing.Point(423, 378);
            this.noSeatsLabel.Name = "noSeatsLabel";
            this.noSeatsLabel.Size = new System.Drawing.Size(84, 17);
            this.noSeatsLabel.TabIndex = 15;
            this.noSeatsLabel.Text = "No of seats:";
            // 
            // clientPhoneTextBox
            // 
            this.clientPhoneTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.clientPhoneTextBox.Location = new System.Drawing.Point(505, 346);
            this.clientPhoneTextBox.Name = "clientPhoneTextBox";
            this.clientPhoneTextBox.Size = new System.Drawing.Size(283, 23);
            this.clientPhoneTextBox.TabIndex = 16;
            // 
            // noSeatsTextBox
            // 
            this.noSeatsTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.noSeatsTextBox.Location = new System.Drawing.Point(505, 375);
            this.noSeatsTextBox.Name = "noSeatsTextBox";
            this.noSeatsTextBox.Size = new System.Drawing.Size(283, 23);
            this.noSeatsTextBox.TabIndex = 17;
            // 
            // reserveButton
            // 
            this.reserveButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.reserveButton.Location = new System.Drawing.Point(409, 405);
            this.reserveButton.Name = "reserveButton";
            this.reserveButton.Size = new System.Drawing.Size(379, 33);
            this.reserveButton.TabIndex = 18;
            this.reserveButton.Text = "Create Reservation";
            this.reserveButton.UseVisualStyleBackColor = true;
            this.reserveButton.Click += new System.EventHandler(this.reserveButton_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.reserveButton);
            this.Controls.Add(this.noSeatsTextBox);
            this.Controls.Add(this.clientPhoneTextBox);
            this.Controls.Add(this.noSeatsLabel);
            this.Controls.Add(this.clientPhoneLabel);
            this.Controls.Add(this.clientNameLabel);
            this.Controls.Add(this.clientNameTextBox);
            this.Controls.Add(this.clientsTableLabel);
            this.Controls.Add(this.clientsTable);
            this.Controls.Add(this.clearFiltersButton);
            this.Controls.Add(this.searchRideButton);
            this.Controls.Add(this.departureLabel);
            this.Controls.Add(this.departureDateTimePicker);
            this.Controls.Add(this.destinationLabel);
            this.Controls.Add(this.destinationTextBox);
            this.Controls.Add(this.ridesListLabel);
            this.Controls.Add(this.ridesTable);
            this.Controls.Add(this.logOutButton);
            this.Controls.Add(this.welcomeLabel);
            this.Name = "MainForm";
            this.Text = "MainForm";
            ((System.ComponentModel.ISupportInitialize)(this.ridesTable)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.clientsTable)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label welcomeLabel;
        private System.Windows.Forms.Button logOutButton;
        private System.Windows.Forms.DataGridView ridesTable;
        private System.Windows.Forms.Label ridesListLabel;
        private System.Windows.Forms.TextBox destinationTextBox;
        private System.Windows.Forms.Label destinationLabel;
        private System.Windows.Forms.DateTimePicker departureDateTimePicker;
        private System.Windows.Forms.Label departureLabel;
        private System.Windows.Forms.Button searchRideButton;
        private System.Windows.Forms.Button clearFiltersButton;
        private System.Windows.Forms.DataGridView clientsTable;
        private System.Windows.Forms.Label clientsTableLabel;
        private System.Windows.Forms.TextBox clientNameTextBox;
        private System.Windows.Forms.Label clientNameLabel;
        private System.Windows.Forms.Label clientPhoneLabel;
        private System.Windows.Forms.Label noSeatsLabel;
        private System.Windows.Forms.TextBox clientPhoneTextBox;
        private System.Windows.Forms.TextBox noSeatsTextBox;
        private System.Windows.Forms.Button reserveButton;
    }
}