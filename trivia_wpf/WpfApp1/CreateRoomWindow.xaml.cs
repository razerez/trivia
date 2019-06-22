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
    /// Interaction logic for CreateRoomWindow.xaml
    /// </summary>
    public partial class CreateRoomWindow : Window
    {
        private Program _p;
        public CreateRoomWindow(Program p)
        {
            InitializeComponent();
            this._p = p;
        }


        public bool createRoom()
        {
            return this._p.createRoom(roomNameTextBox.Text, maxPlayersTextBox.Text, questionsNumTextBox.Text, questionTimeTextBox.Text);
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(this._p, true);
            menu.Show();
            this.Close();
        }

        private void Send_Click(object sender, RoutedEventArgs e)
        {
            createRoom();
            WaitingRoomWindow waiting = new WaitingRoomWindow(this._p ,true,
                                                           roomNameTextBox.Text, maxPlayersTextBox.Text, questionsNumTextBox.Text, questionTimeTextBox.Text);
            waiting.Show();
            this.Close();
        }
    }
}
