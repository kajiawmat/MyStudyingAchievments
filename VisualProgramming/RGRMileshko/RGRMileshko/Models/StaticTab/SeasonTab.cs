using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using RGRMileshko.Models.Database;
using System.Linq;

namespace RGRMileshko.Models.StaticTabs
{
    public class SeasonTab : StaticTab
    {
        public SeasonTab(string h = "", DbSet<Season>? dBS = null) : base(h)
        {
            DBS = dBS;
            DataColumns = new List<string>();
            DataColumns.Add("YearFrom");
            DataColumns.Add("YearTo");
            DataColumns.Add("Winner");
            DataColumns.Add("RunnerUp");
            DataColumns.Add("Deleting");
            ObjectList = DBS.ToList<object>();
            ObjectList.Add(false);
        }

        new public DbSet<Season>? DBS { get; set; }
    }
}
