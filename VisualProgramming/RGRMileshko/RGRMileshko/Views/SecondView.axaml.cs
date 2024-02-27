using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using Avalonia.Interactivity;
using RGRMileshko.ViewModels;

namespace RGRMileshko.Views
{
    public partial class SecondView : UserControl
    {
        public SecondView()
        {
            InitializeComponent();
            this.FindControl<Button>("SELECT").Click += ClickEventSelect;
            this.FindControl<Button>("JOIN").Click += ClickEventJoin;
            this.FindControl<Button>("GROUP").Click += ClickEventGroup;
        }

        private void InitializeComponent()
        {
            AvaloniaXamlLoader.Load(this);
        }
        private async void ClickEventSelect(object? sender, RoutedEventArgs e)
        {
            var window = new SelectDBView((this.DataContext as SecondViewModel).MainContext);
            await window.ShowDialog((Window)this.VisualRoot);
        }
        private async void ClickEventJoin(object? sender, RoutedEventArgs e)
        {
            var window = new JoinDBView((this.DataContext as SecondViewModel).MainContext);
            await window.ShowDialog((Window)this.VisualRoot);
        }
        private async void ClickEventGroup(object? sender, RoutedEventArgs e)
        {
            var window = new GroupDBView((this.DataContext as SecondViewModel).MainContext);
            await window.ShowDialog((Window)this.VisualRoot);
        }
    }
}
