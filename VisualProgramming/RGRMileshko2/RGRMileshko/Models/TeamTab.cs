using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using RGRMileshko.Models.Database;
using System.Linq;

namespace RGRMileshko.Models.StaticTabs
{
    public class TeamTab : StaticTab
    {
        public TeamTab(string h = "", DbSet<Team>? dBS = null) : base(h)
        {
            DBS = dBS;
            DataColumns = new List<string>(); 
            DataColumns.Add("TeamName");
            DataColumns.Add("Division");
            DataColumns.Add("YearFrom");
            DataColumns.Add("YearTo");
            ObjectList = DBS.ToList<object>();
        }

        new public DbSet<Team>? DBS { get; set; }
    }
}
