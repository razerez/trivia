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
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : Window
    {
        private Program _p;
        public Menu(Program p)
        {
            InitializeComponent();
            this._p = p;
        }

        private void Sign_In_Click(object sender, RoutedEventArgs e)
        {
            if (Check_info(usernameTextBox.Text, passwordTextBox.Text))
            {
                SignIn.Visibility = Visibility.Hidden;
                username.Visibility = Visibility.Visible;
                usernameTop.Visibility = Visibility.Visible;
                signUpButton.Visibility = Visibility.Hidden;
                LogOutButton.Visibility = Visibility.Visible;
                JoinRoomButton.IsEnabled = true;
                createRoomButton.IsEnabled = true;
                myStatusButton.IsEnabled = true;
                bestScoresButton.IsEnabled = true;
            }


        }
        private bool Check_info(string username, string password)
        {
            return this._p.login(username, password);

        }

        private void UsernameTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            usernameTop.Text = usernameTextBox.Text;
            username.Text = "Hello " + usernameTextBox.Text;
            
        }

        private void QuitButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void SignUpButton_Click(object sender, RoutedEventArgs e)
        {
            SignUpWindow signup = new SignUpWindow();
            signup.Show();
            this.Close();
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            JoinRoomWindow joinRoom= new JoinRoomWindow();
            joinRoom.Show();
            this.Close();
        }

        private void MyStatusButton_Click(object sender, RoutedEventArgs e)
        {
            StatusWindow status = new StatusWindow();
            status.Show();
            this.Close();
        }

        private void BestScoresButton_Click(object sender, RoutedEventArgs e)
        {
            HighscoresWindow highScores = new HighscoresWindow();
            highScores.Show();
            this.Close();
        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomWindow createRoom = new CreateRoomWindow();
            createRoom.Show();
            this.Close();
        }
    }
}
