using OnwardTravel.Services.Exceptions;
using System;
using System.Windows.Forms;

namespace OnwardTravel.Client
{
    internal partial class LoginForm : Form
    {
        private ClientController _ctrl;
        public LoginForm()
        {
            InitializeComponent();
        }

        public void SetController(ClientController ctrl)
        {
            _ctrl = ctrl;
        }

        private void loginButton_Click(object sender, EventArgs e)
        {
            string username = usernameTextBox.Text;
            string password = passwordTextBox.Text;
            try
            {
                _ctrl.Login(username, password);
                usernameTextBox.Text = null;
                passwordTextBox.Text = null;
                MainForm form = new MainForm();
                form.SetParent(this);
                //form.FormClosed += reactOnMainFormClosed;
                form.SetController(_ctrl);
                form.Show();
                Hide();
            }
            catch (InvalidDataException ex)
            {
                MessageBox.Show(ex.Message, "Login Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void reactOnMainFormClosed(object send, EventArgs e)
        {
            Close();
        }
    }
}
