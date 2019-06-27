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
    /// Interaction logic for StatusWindow.xaml
    /// </summary>
    public partial class StatusWindow : Window
    {
        private Program _p;
        public StatusWindow(Program p)
        {
            InitializeComponent();
            this._p = p;
            usernameTop.Text = this._p._username;
            usernameTop.Visibility = Visibility.Visible;
            _p.myStatus();
        
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(this._p, true);
            menu.Show();
            this.Close();
        }
        private void ChangeGameNum(int num)
        {
            gameNum.Text = "number of games: " + num.ToString();
        }        
        private void ChangeRightAnswersNum(int num)
        {
            rightAnswersNum.Text = "number of right answers: " + num.ToString();
        }        
        private void ChangeWrongAnswersNum(int num)
        {
            wrongAnswersNum.Text = "number of wrong answers: " + num.ToString();
        }
        private void ChangeAvergeTimeNum(int num)
        {
            avarageTimeNum.Text = "average time for answer: " + num.ToString();
        }
    }
}
