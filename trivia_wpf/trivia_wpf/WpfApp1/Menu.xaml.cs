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
        public Menu(Program p, bool loggedIn)
        {
            InitializeComponent();
            this._p = p;
            JoinRoomButton.IsEnabled = true;//\\
            if(loggedIn)
            {
                secondView();
                username.Text = "Hello " +  this._p._username;
                usernameTop.Text = this._p._username;
            }
            else
            {
                firstView();
            }
        }


        public void firstView()
        {
            error.Visibility = Visibility.Hidden;
            LogOutButton.Visibility = Visibility.Hidden;
            signUpButton.Visibility = Visibility.Visible;
            SignIn.Visibility = Visibility.Visible;
            username.Visibility = Visibility.Hidden;
            usernameTop.Visibility = Visibility.Hidden;
            JoinRoomButton.IsEnabled = false;
            createRoomButton.IsEnabled = false;
            myStatusButton.IsEnabled = false;
            bestScoresButton.IsEnabled = false;
        }

        public void secondView()
        {
            error.Visibility = Visibility.Hidden;
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

        private void Sign_In_Click(object sender, RoutedEventArgs e)
        {
            if (usernameTextBox.Text == "" || passwordTextBox.Text == "")
                return;
            if (Check_info(usernameTextBox.Text, passwordTextBox.Text))
            {
                secondView();
            }
            else
            {
                error.Visibility = Visibility.Visible;
            }
        }
        private bool Check_info(string username, string password)
        {
            return this._p.Login(username, password);

        }

        private void UsernameTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            usernameTop.Text = usernameTextBox.Text;
            username.Text = "Hello " + usernameTextBox.Text;
            
        }

        private void QuitButton_Click(object sender, RoutedEventArgs e)
        {
            this._p.Exit();
            this.Close();
        }

        private void SignUpButton_Click(object sender, RoutedEventArgs e)
        {
            SignUpWindow signup = new SignUpWindow(this._p);
            signup.Show();
            this.Close();
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            JoinRoomWindow joinRoom= new JoinRoomWindow(this._p);
            joinRoom.Show();
            this.Close();
        }

        private void MyStatusButton_Click(object sender, RoutedEventArgs e)
        {
            StatusWindow status = new StatusWindow(this._p);
            status.Show();
            this.Close();
        }

        private void BestScoresButton_Click(object sender, RoutedEventArgs e)
        {
            HighscoresWindow highScores = new HighscoresWindow(this._p);
            highScores.Show();
            this.Close();
        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomWindow createRoom = new CreateRoomWindow(this._p);
            createRoom.Show();
            this.Close();
        }

        private void logOutClick(object sender, RoutedEventArgs e)
        {
            this._p.Logout();
            firstView();
        }

    }
}
