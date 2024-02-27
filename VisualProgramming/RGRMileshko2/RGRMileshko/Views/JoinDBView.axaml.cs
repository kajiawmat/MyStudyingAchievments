using Avalonia;
using Avalonia.Interactivity;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using System.Linq;
using RGRMileshko.Models;
using RGRMileshko.ViewModels;
using System.Collections.Generic;

namespace RGRMileshko.Views
{
    public partial class JoinDBView : Window
    {
        public JoinDBView()
        {
            InitializeComponent();
#if DEBUG
            this.AttachDevTools();
#endif
            this.FindControl<Button>("Confirm").Click += button_Confirm_Click;
            this.FindControl<Button>("Cancel").Click += button_Cancel_Click;
        }
        public JoinDBView(MainWindowViewModel? mainContext) : this()
        {
            this.DataContext = new JoinDBViewModel(mainContext);
        }

        private void InitializeComponent()
        {
            AvaloniaXamlLoader.Load(this);
        }
        private void button_Confirm_Click(object? sender, RoutedEventArgs e)
        {
            var StringTrunc = (string str, int length) =>
            {
                if (str.Length < length)
                {
                    return str;
                }
                return str.Substring(0, length);
            };
            var dc = (this.DataContext as JoinDBViewModel);
            List<object> newList = (from f in dc.FirstSelectedTab.ObjectList
                                    join s in dc.SecondSelectedTab.ObjectList
                                    on f.GetType().GetProperty(dc.FirstSelectedField).GetValue(f)
                                    equals s.GetType().GetProperty(dc.SecondSelectedField).GetValue(s)
                                    select TypeMerger.TypeMerger.Merge(f, s)).ToList<object>();
            var newQuery =
                new Query(
                string.Format("{0}_J_{1}",
                    StringTrunc(dc.FirstSelectedTab.Header, 3), StringTrunc(dc.SecondSelectedTab.Header, 3)),
                string.Format("{0} JOIN {1} ON {0}.{2} EQUALS {1}.{3}",
                dc.FirstSelectedTab.Header, dc.SecondSelectedTab.Header,
                dc.FirstSelectedField, dc.SecondSelectedField));
            var newTab = new DynamicTab(
                string.Format("{0}_J_{1}",
                    StringTrunc(dc.FirstSelectedTab.Header, 3), StringTrunc(dc.SecondSelectedTab.Header, 3)),
                newList);
            newTab.DataColumns = new List<string>();
            newTab.DataColumns.AddRange(dc.FirstSelectedTab.DataColumns);
            newTab.DataColumns.AddRange(dc.SecondSelectedTab.DataColumns);
            newQuery.BindedTab = newTab;
            newTab.BindedQuery = newQuery;
            dc.MainContext.Queries.Add(newQuery);
            dc.MainContext.Tabs.Add(newTab);
            this.Close();
        }
        private void button_Cancel_Click(object? sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
