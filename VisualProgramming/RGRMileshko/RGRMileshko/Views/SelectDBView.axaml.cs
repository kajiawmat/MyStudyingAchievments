using Avalonia;
using Avalonia.Interactivity;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using System.Linq;
using System.Linq.Expressions;
using System.Linq.Dynamic.Core;
using RGRMileshko.Models;
using RGRMileshko.ViewModels;
using System.Collections.Generic;

namespace RGRMileshko.Views
{
    public partial class SelectDBView : Window
    {
        public SelectDBView()
        {
            InitializeComponent();
#if DEBUG
            this.AttachDevTools();
#endif
            this.FindControl<Button>("Confirm").Click += button_Confirm_Click;
            this.FindControl<Button>("Cancel").Click += button_Cancel_Click;
        }
        public SelectDBView(MainWindowViewModel? mainContext) : this()
        {
            this.DataContext = new SelectDBViewModel(mainContext);
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
            var dc = (this.DataContext as SelectDBViewModel);
            var p = Expression.Parameter(dc.SelectedTab.ObjectList.FirstOrDefault().GetType(),
                dc.SelectedTab.ObjectList.FirstOrDefault().GetType().Name);
            var exp = DynamicExpressionParser
                    .ParseLambda(new[] { p }, null, dc.Where).Compile();
            List<object> newList = new();
            foreach (var item in dc.SelectedTab.ObjectList)
            {
                if (exp.DynamicInvoke(item) as bool? == true)
                {
                    newList.Add(item);
                }
            }
            var newQuery =
                new Query(
                string.Format("{0}_S", StringTrunc(dc.SelectedTab.Header, 3)),
                string.Format("{0} SELECT WHERE {1}", dc.SelectedTab.Header, dc.Where));
            var newTab = new DynamicTab(
                string.Format("{0}_S", StringTrunc(dc.SelectedTab.Header, 3)), newList);
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
