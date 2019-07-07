using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for SignUpWindow.xaml
    /// </summary>
    public partial class SignUpWindow : Window
    {
        private Program _p;
        public SignUpWindow(Program p)
        {
            InitializeComponent();
            this._p = p;
        }

        bool IsValidEmail(string email)
        {
            try
            {
                var addr = new System.Net.Mail.MailAddress(email);
                return addr.Address == email;
            }
            catch
            {
                return false;
            }
        }


        private void Sign_Up_Click(object sender, RoutedEventArgs e)
        {
            _p._username = usernameTextBox.Text;
            if (passwordTextBox.Text == "" || usernameTextBox.Text == "" || !IsValidEmail(emailTextBox.Text) || passwordTextBox.Text.Length < 8 || usernameTextBox.Text.Length >= 8)
            {
                error.Visibility = Visibility.Visible;
                return;
            }
            if (this._p.Signup(passwordTextBox.Text, emailTextBox.Text))
            {
                error.Visibility = Visibility.Hidden;
                Menu menu = new Menu(this._p, true);
                menu.Show();
                this.Close();
            }
            else
            {
                error.Visibility = Visibility.Visible;
            }
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(this._p,false);
            menu.Show();
            this.Close();
        }

        private void UsernameTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}
