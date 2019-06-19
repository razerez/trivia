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
    /// Interaction logic for JoinRoomWindow.xaml
    /// </summary>
    public partial class JoinRoomWindow : Window
    {
        public JoinRoomWindow()
        {
            InitializeComponent();
            
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu();
            menu.Show();
            this.Close();
        }

        private void Add_Room(string name)
        {
            rooms.Items.Add(name);
        }

        private void Add_Player(string name)
        {
            players.Items.Add(name);
        }
        private void Refresh_Click(object sender, RoutedEventArgs e)
        {
            rooms.SelectedItem = null;
            roomGrid.Visibility = Visibility.Hidden;
            JoinButton.IsEnabled = false;
        }

        private void Join_Click(object sender, RoutedEventArgs e)
        {
            if(!string.IsNullOrEmpty(rooms.Text))//check if room is selected
            {
                WaitingRoomWindow waiting = new WaitingRoomWindow(false);
                waiting.Show();
                this.Close();
            }
        }

        private void Rooms_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            JoinButton.IsEnabled = true;
            roomGrid.Visibility = Visibility.Visible;
        }
    }
}
