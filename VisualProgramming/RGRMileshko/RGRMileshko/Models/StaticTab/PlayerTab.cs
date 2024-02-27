using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using RGRMileshko.Models.Database;
using System.Linq;

namespace RGRMileshko.Models.StaticTabs
{
    public class PlayerTab : StaticTab
    {
        public PlayerTab(string h = "", DbSet<Player>? dBS = null) : base(h)
        {
            DBS = dBS;
            DataColumns = new List<string>();
            DataColumns.Add("Name");
            DataColumns.Add("TeamName");
            DataColumns.Add("Age");
            DataColumns.Add("Position");
            DataColumns.Add("Height");
            DataColumns.Add("Weight");
            DataColumns.Add("Country");
            DataColumns.Add("YearFrom");
            DataColumns.Add("YearTo");
            DataColumns.Add("Deleting");
            ObjectList = DBS.ToList<object>();
            ObjectList.Add(false);
        }

        new public DbSet<Player>? DBS { get; set; }
    }
}
