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
    public partial class GroupDBView : Window
    {
        public GroupDBView()
        {
            InitializeComponent();
#if DEBUG
            this.AttachDevTools();
#endif
            this.FindControl<Button>("Confirm").Click += button_Confirm_Click;
            this.FindControl<Button>("Cancel").Click += button_Cancel_Click;
        }
        public GroupDBView(MainWindowViewModel? mainContext) : this()
        {
            this.DataContext = new GroupDBViewModel(mainContext);
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
            var dc = (this.DataContext as GroupDBViewModel);
            var group = (from o in dc.SelectedTab.ObjectList
                         group o by o.GetType().GetProperty(dc.SelectedField).GetValue(o));
            List<object> newList = new List<object>();
            foreach (var l in group)
            {
                newList.AddRange(l.ToList<object>());
            }
            var newQuery =
                new Query(
                string.Format("{0}_G_{1}",
                    StringTrunc(dc.SelectedTab.Header, 3), StringTrunc(dc.SelectedField, 3)),
                string.Format("{0} GROUPBY {1}", dc.SelectedTab.Header, dc.SelectedField));
            var newTab = new DynamicTab(
                string.Format("{0}_G_{1}",
                    StringTrunc(dc.SelectedTab.Header, 3), StringTrunc(dc.SelectedField, 3)),
                newList);
            newTab.DataColumns = dc.SelectedTab.DataColumns;
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
