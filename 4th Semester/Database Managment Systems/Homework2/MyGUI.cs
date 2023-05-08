using Contests.Utils;
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Drawing.Text;
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
        
        private string parentTableName = Program.GetAppSettingsByName("ParentTable");
        private string parentIDColumn = Program.GetAppSettingsByName("ParentIDColumn");

        private string childTableName = Program.GetAppSettingsByName("ChildTable");
        private string childIDColumn = Program.GetAppSettingsByName("ChildIDColumn");

        private string childColumnsString = Program.GetAppSettingsByName("ChildColumns");
        private string[] childColumns = Program.GetAppSettingsByName("ChildColumns").Split(',');
        private string childParamsString = Program.GetAppSettingsByName("ChildParameters");
        private string[] childParams = Program.GetAppSettingsByName("ChildParameters").Split(',');

        private string childUpdateQuery = Program.GetAppSettingsByName("ChildUpdateQuery");
        private string childDeleteQuery = Program.GetAppSettingsByName("ChildDeleteQuery");
 
        private IDictionary<string, TextBox> boxes = new Dictionary<string, TextBox>();

        public MyGUI()
        {
            InitializeComponent();
            
            da.SelectCommand = new SqlCommand("SELECT * FROM " + parentTableName, DbUtils.Connection);
            dsParentTable.Clear();
            da.Fill(dsParentTable);

            parentTable.DataSource = dsParentTable.Tables[0];
            bsParentTable.DataSource = dsParentTable.Tables[0];

            designTable(parentTable);
            designTable(childTable);

            int i = 1;
            foreach (var childColumn in childColumns)
            {
                if (childColumn != parentIDColumn)
                {
                    var lbl = new Label
                    {
                        Text = childColumn,
                        Location = new System.Drawing.Point(10, i * 25)
                    };
                    var txtBox = new TextBox
                    {
                        Location = new System.Drawing.Point(120, i * 25),
                        Size = new System.Drawing.Size(500, 30)
                    };

                    textBoxesPanel.Controls.Add(lbl);
                    textBoxesPanel.Controls.Add(txtBox);
                    boxes.Add(childColumn, txtBox);
                    i++;
                }
            }
            parentTableLabel.Text = $"{parentTableName} Table";
            childTableLabel.Text = $"{childTableName} Table";
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
            da.SelectCommand = new SqlCommand("SELECT * FROM " + childTableName + " WHERE " + parentIDColumn + " = @id", DbUtils.Connection);
            da.SelectCommand.Parameters.Add("@id", SqlDbType.Int).Value = selectedParentID;

            dsChildTable.Clear();
            da.Fill(dsChildTable);

            childTable.DataSource = dsChildTable.Tables[0];
            bsChildTable.DataSource = dsChildTable.Tables[0];
        }

        private void parentTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0)
                return;
            var selectedCoordinatorRow = parentTable.Rows[e.RowIndex];
            if (selectedCoordinatorRow.Cells[0].Value.ToString() == "")
            {
                selectedParentID = -1;
                return;
            }
            selectedParentID = int.Parse(selectedCoordinatorRow.Cells[0].Value.ToString());

            refreshChildTable();
        }

        private void childTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0)
            {
                selectedChildID = -1;
                foreach (var box in boxes.Values)
                {
                    box.Text = "";
                }
                return;
            }
            var selectedStudentRow = childTable.Rows[e.RowIndex];
            if (selectedStudentRow.Cells[0].Value.ToString() == "")
            {
                selectedChildID = -1;
                foreach (var box in boxes.Values)
                {
                    box.Text = "";
                }
                return;
            }
            selectedChildID = int.Parse(selectedStudentRow.Cells[0].Value.ToString());
            int i = 1;
            foreach (var column in childColumns)
            {
                if (column != parentIDColumn)
                {
                    boxes[column].Text = selectedStudentRow.Cells[i].Value.ToString();
                    i++;
                }
            }
        }

        private void insertButton_Click(object sender, EventArgs e)
        {
            if (selectedParentID == -1)
            {
                MessageBox.Show("Please select an item from the parent table first first!", "Insertion Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            foreach (var box in boxes.Values)
            {
                if (box.Text == "")
                {
                    MessageBox.Show("Please complete all the fields!", "Insertion Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }

            da.InsertCommand = new SqlCommand($"INSERT INTO {childTableName} ({childColumnsString}) VALUES ({childParamsString})", DbUtils.Connection);
            for (int i = 0; i < childColumns.Length; i++)
            {
                if (childColumns[i] != parentIDColumn)
                {
                    da.InsertCommand.Parameters.Add(childParams[i], SqlDbType.VarChar).Value = boxes[childColumns[i]].Text;
                }
            }
            da.InsertCommand.Parameters.Add("@" + parentIDColumn, SqlDbType.Int).Value = selectedParentID;
            try
            {
                da.InsertCommand.ExecuteNonQuery();
            }
            catch (SqlException ex)
            {
                MessageBox.Show(ex.Message, "Insertion Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

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

            da.UpdateCommand = new SqlCommand(childUpdateQuery, DbUtils.Connection);
            for (int i = 0; i < childColumns.Length; i++)
            {
                if (childColumns[i] != parentIDColumn)
                {
                    da.UpdateCommand.Parameters.Add(childParams[i], SqlDbType.VarChar).Value = boxes[childColumns[i]].Text;
                }
            }
            da.UpdateCommand.Parameters.Add("@" + childIDColumn, SqlDbType.Int).Value = selectedChildID;
            try
            {
                da.UpdateCommand.ExecuteNonQuery();
            }
            catch (SqlException ex)
            {
                MessageBox.Show(ex.Message, "Update Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

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
                da.DeleteCommand = new SqlCommand(childDeleteQuery, DbUtils.Connection);
                da.DeleteCommand.Parameters.Add("@" + childIDColumn, SqlDbType.Int).Value = selectedChildID;
                try
                {
                    da.DeleteCommand.ExecuteNonQuery();
                }
                catch (SqlException ex)
                {
                    MessageBox.Show(ex.Message, "Deletion Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

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
