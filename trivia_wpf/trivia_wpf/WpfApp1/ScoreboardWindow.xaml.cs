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
    /// Interaction logic for ScoreboardWindow.xaml
    /// </summary>
    public partial class ScoreboardWindow : Window
    {
        public ScoreboardWindow(Score[] scoreArr)
        {
            InitializeComponent();
            int top = 10;
            int bot = 40;
            int left = 50;
            int right = 50;
            for (int i = 0; i < scoreArr.Length; i++)
            {
                TextBlock score = new TextBlock();
                score.Text = "username: " + scoreArr[i]._username + "   score: " + scoreArr[i]._score;
                score.FontSize = 20;
                score.FontWeight = FontWeights.Bold;
                score.TextAlignment = TextAlignment.Center;
                score.Margin= new Thickness(left, top, right, bot);
                top += 20;
                bot -= 20;
                score.TextWrapping = TextWrapping.Wrap;
                winGrid.Children.Add(score);
            }
        }
    }
}
