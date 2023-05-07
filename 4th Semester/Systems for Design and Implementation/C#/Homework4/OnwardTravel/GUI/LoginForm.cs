using OnwardTravel.Models;
using OnwardTravel.Service;
using OnwardTravel.Service.Exceptions;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OnwardTravel.GUI
{
    internal partial class LoginForm : Form
    {
        private UserService _userService;
        public LoginForm()
        {
            InitializeComponent();
        }

        public void SetService(UserService userService)
        {
            _userService = userService;
        }

        private void loginButton_Click(object sender, EventArgs e)
        {
            string username = usernameTextBox.Text;
            string password = passwordTextBox.Text;
            try
            {
                User user = _userService.TryLogin(username, password);
                usernameTextBox.Text = null;
                passwordTextBox.Text = null;
                MainForm form = new MainForm();
                form.SetParent(this);
                //form.FormClosed += reactOnMainFormClosed;
                form.SetService(_userService);
                form.SetUser(user);
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
