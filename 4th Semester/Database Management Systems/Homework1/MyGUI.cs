using Contests.Utils;
using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Contests
{
    public partial class MyGUI : Form
    {
        private readonly SqlDataAdapter da = new SqlDataAdapter();
        private readonly DataSet dsParentTable = new DataSet();
        private readonly DataSet dsChildTable = new DataSet();
        private readonly BindingSource bsParentTable = new BindingSource();
        private readonly BindingSource bsChildTable = new BindingSource();
        private int selectedParentID = -1;
        private int selectedChildID = -1;

        public MyGUI()
        {
            InitializeComponent();
            
            da.SelectCommand = new SqlCommand("SELECT * FROM Coordinators", DbUtils.Connection);
            dsParentTable.Clear();
            da.Fill(dsParentTable);

            coordinatorsTable.DataSource = dsParentTable.Tables[0];
            bsParentTable.DataSource = dsParentTable.Tables[0];

            designTable(coordinatorsTable);
            designTable(studentsTable);

            coordinatorsTable.Columns[0].Visible = false;
        }

        private void designTable(DataGridView table)
        {
            table.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            table.MultiSelect = false;
            table.ReadOnly = true;
            table.AllowUserToResizeRows = false;
            table.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            table.RowHeadersVisible = false;
        }

        private void refreshChildTable()
        {
            da.SelectCommand = new SqlCommand("SELECT * FROM Students WHERE coordinator_id = @id", DbUtils.Connection);
            da.SelectCommand.Parameters.Add("@id", SqlDbType.Int).Value = selectedParentID;

            dsChildTable.Clear();
            da.Fill(dsChildTable);

            studentsTable.DataSource = dsChildTable.Tables[0];
            bsChildTable.DataSource = dsChildTable.Tables[0];

            studentsTable.Columns[0].Visible = false;
            studentsTable.Columns[3].Visible = false;
        }

        private void parentTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0)
                return;
            var selectedCoordinatorRow = coordinatorsTable.Rows[e.RowIndex];
            if (selectedCoordinatorRow.Cells[0].Value.ToString() == "")
            {
                selectedCoordinatorLabel.Text = "-";
                selectedParentID = -1;
                return;
            }
            selectedParentID = int.Parse(selectedCoordinatorRow.Cells[0].Value.ToString());
            selectedCoordinatorLabel.Text = selectedCoordinatorRow.Cells[1].Value.ToString();

            refreshChildTable();
        }

        private void childTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            var selectedStudentRow = studentsTable.Rows[e.RowIndex];
            if (selectedStudentRow.Cells[0].Value.ToString() == "")
            {
                selectedChildID = -1;
                studentNameTextBox.Text = "";
                studentSchoolTextBox.Text = "";
                return;
            }
            selectedChildID = int.Parse(selectedStudentRow.Cells[0].Value.ToString());
            studentNameTextBox.Text = selectedStudentRow.Cells[1].Value.ToString();
            studentSchoolTextBox.Text = selectedStudentRow.Cells[2].Value.ToString();
        }

        private void insertButton_Click(object sender, EventArgs e)
        {
            if (selectedParentID == -1)
            {
                MessageBox.Show("Please select a coordinator first!", "Insertion Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (studentNameTextBox.Text == "" || studentSchoolTextBox.Text == "")
            {
                MessageBox.Show("Please enter a name and a school for the student!", "Insertion Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            da.InsertCommand = new SqlCommand("INSERT INTO Students(name, school, coordinator_id) VALUES (@name, @school, @coordinator_id)", DbUtils.Connection);
            da.InsertCommand.Parameters.Add("@name", SqlDbType.VarChar).Value = studentNameTextBox.Text;
            da.InsertCommand.Parameters.Add("@school", SqlDbType.VarChar).Value = studentSchoolTextBox.Text;
            da.InsertCommand.Parameters.Add("@coordinator_id", SqlDbType.Int).Value = selectedParentID;
            da.InsertCommand.ExecuteNonQuery();

            refreshChildTable();

            MessageBox.Show("Record has been inserted!", "Insertion Successful", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            if (selectedChildID == -1)
            {
                MessageBox.Show("Please select a student first!", "Update Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            da.UpdateCommand = new SqlCommand("UPDATE Students SET name = @name, school = @school WHERE student_id = @student_id", DbUtils.Connection);
            da.UpdateCommand.Parameters.Add("@name", SqlDbType.VarChar).Value = studentNameTextBox.Text;
            da.UpdateCommand.Parameters.Add("@school", SqlDbType.VarChar).Value = studentSchoolTextBox.Text;
            da.UpdateCommand.Parameters.Add("@student_id", SqlDbType.Int).Value = selectedChildID;
            da.UpdateCommand.ExecuteNonQuery();

            refreshChildTable();

            MessageBox.Show("Record has been updated!", "Update Successful", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            if (selectedChildID == -1)
            {
                MessageBox.Show("Please select a student first!", "Deletion Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (MessageBox.Show("Are you sure?\nNo undo after delete", "Confirm Deletion", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.Yes)
            {
                da.DeleteCommand = new SqlCommand("DELETE FROM Students WHERE student_id = @student_id", DbUtils.Connection);
                da.DeleteCommand.Parameters.Add("@student_id", SqlDbType.Int).Value = selectedChildID;
                da.DeleteCommand.ExecuteNonQuery();

                refreshChildTable();

                MessageBox.Show("Record has been deleted!", "Deletion Successful", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("Record has not been deleted!", "Deletion Canceled", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
    }
}
