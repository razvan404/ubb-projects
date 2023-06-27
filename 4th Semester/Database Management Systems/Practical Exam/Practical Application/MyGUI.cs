using Practical.Utils;
using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Practical
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
            
            da.SelectCommand = new SqlCommand("SELECT * FROM Pictori", ConnectionFactory.Connection);
            dsParentTable.Clear();
            da.Fill(dsParentTable);

            parentTable.DataSource = dsParentTable.Tables[0];
            bsParentTable.DataSource = dsParentTable.Tables[0];

            designTable(parentTable);
            designTable(childTable);

            parentTable.Columns[0].Visible = false;
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
            da.SelectCommand = new SqlCommand("SELECT * FROM Tablouri WHERE Pid = @id", ConnectionFactory.Connection);
            da.SelectCommand.Parameters.Add("@id", SqlDbType.Int).Value = selectedParentID;

            dsChildTable.Clear();
            da.Fill(dsChildTable);

            childTable.DataSource = dsChildTable.Tables[0];
            bsChildTable.DataSource = dsChildTable.Tables[0];

            childTable.Columns[0].Visible = false;
            childTable.Columns[4].Visible = false;
        }

        private void parentTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0)
                return;
            var selectedCoordinatorRow = parentTable.Rows[e.RowIndex];
            if (selectedCoordinatorRow.Cells[0].Value.ToString() == "")
            {
                selectedLabel.Text = "-";
                selectedParentID = -1;
                return;
            }
            selectedParentID = int.Parse(selectedCoordinatorRow.Cells[0].Value.ToString());
            selectedLabel.Text = selectedCoordinatorRow.Cells[1].Value.ToString();

            refreshChildTable();
        }

        private void childTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            var selectedStudentRow = childTable.Rows[e.RowIndex];
            if (selectedStudentRow.Cells[0].Value.ToString() == "")
            {
                selectedChildID = -1;
                textBox1.Text = "";
                textBox2.Text = "";
                return;
            }
            selectedChildID = int.Parse(selectedStudentRow.Cells[0].Value.ToString());
            textBox1.Text = selectedStudentRow.Cells[1].Value.ToString();
            textBox2.Text = selectedStudentRow.Cells[2].Value.ToString();
            textBox3.Text = selectedStudentRow.Cells[3].Value.ToString();
            textBox4.Text = selectedStudentRow.Cells[5].Value.ToString();
        }

        private void insertButton_Click(object sender, EventArgs e)
        {
            try 
            {
                if (selectedParentID == -1)
                {
                    MessageBox.Show("Selecteaza prima data un pictor!", "Insertion Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                da.InsertCommand = new SqlCommand("INSERT INTO Tablouri(Denumire, AnPictura, Dimensiune, Pid, Mid) VALUES (@den, @anp, @dim, @pid, @mid)", ConnectionFactory.Connection);
                da.InsertCommand.Parameters.Add("@den", SqlDbType.VarChar).Value = textBox1.Text;
                da.InsertCommand.Parameters.Add("@anp", SqlDbType.Int).Value = int.Parse(textBox2.Text);
                da.InsertCommand.Parameters.Add("@dim", SqlDbType.VarChar).Value = textBox3.Text;
                da.InsertCommand.Parameters.Add("@pid", SqlDbType.Int).Value = selectedParentID;
                da.InsertCommand.Parameters.Add("@mid", SqlDbType.Int).Value = int.Parse(textBox4.Text);
                da.InsertCommand.ExecuteNonQuery();

                refreshChildTable();

                MessageBox.Show("Tabloul a fost adaugat cu succes!", "Insertion Successful", MessageBoxButtons.OK, MessageBoxIcon.Information);
            } 
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Insertion failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
            
            }
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            try
            {
                if (selectedChildID == -1)
                {
                    MessageBox.Show("Selecteaza prima data un tablou!", "Update Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                da.UpdateCommand = new SqlCommand("UPDATE Tablouri SET Denumire = @den, AnPictura = @anp, Dimensiune = @dim, Mid = @mid WHERE Tid = @tid", ConnectionFactory.Connection);
                da.UpdateCommand.Parameters.Add("@den", SqlDbType.VarChar).Value = textBox1.Text;
                da.UpdateCommand.Parameters.Add("@anp", SqlDbType.Int).Value = int.Parse(textBox2.Text);
                da.UpdateCommand.Parameters.Add("@dim", SqlDbType.VarChar).Value = textBox3.Text;
                da.UpdateCommand.Parameters.Add("@mid", SqlDbType.Int).Value = int.Parse(textBox4.Text);
                da.UpdateCommand.Parameters.Add("@tid", SqlDbType.Int).Value = selectedChildID;
                da.UpdateCommand.ExecuteNonQuery();

                refreshChildTable();

                MessageBox.Show("Tabloul a fost actualizat cu succes!", "Update Successful", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Update failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            try
            {
                if (selectedChildID == -1)
                {
                    MessageBox.Show("Selecteaza prima data un tablou!", "Deletion Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                if (MessageBox.Show("Esti sigur ca vrei sa stergi acest tablou?\nNu poti anula operatia!", "Confirm Deletion", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.Yes)
                {
                    da.DeleteCommand = new SqlCommand("DELETE FROM Tablouri WHERE Tid = @tid", ConnectionFactory.Connection);
                    da.DeleteCommand.Parameters.Add("@tid", SqlDbType.Int).Value = selectedChildID;
                    da.DeleteCommand.ExecuteNonQuery();

                    refreshChildTable();

                    MessageBox.Show("Tabloul a fost sters cu succes!", "Deletion Successful", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                else
                {
                    MessageBox.Show("Operatie anulata cu succes!", "Deletion Canceled", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Deletion failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
