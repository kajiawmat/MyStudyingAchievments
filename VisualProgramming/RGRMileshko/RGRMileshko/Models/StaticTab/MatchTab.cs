using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using RGRMileshko.Models.Database;
using System.Linq;

namespace RGRMileshko.Models.StaticTabs
{
    public class MatchTab : StaticTab
    {
        public MatchTab(string h = "", DbSet<Match>? dBS = null) : base(h)
        {
            DBS = dBS;
            DataColumns = new List<string>();
            DataColumns.Add("GameNumber");
            DataColumns.Add("SeasonYear");
            DataColumns.Add("Date");
            DataColumns.Add("Arena");
            DataColumns.Add("Deleting");
            ObjectList = DBS.ToList<object>();
            ObjectList.Add(false);
        }

        new public DbSet<Match>? DBS { get; set; }
    }
}
