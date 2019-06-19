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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class NoServerRuning : Window
    {
        public NoServerRuning()
        {
            InitializeComponent();
        }

        private void Abort_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Try_again_Click(object sender, RoutedEventArgs e)
        {
            Program p = new Program();
            this.Close();
        }
    }
}
