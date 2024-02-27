using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using RGRMileshko.Models.Database;
using System.Linq;

namespace RGRMileshko.Models.StaticTabs
{
    public class TeamStatisticTab : StaticTab
    {
        public TeamStatisticTab(string h = "", DbSet<TeamStatistic>? dBS = null) : base(h)
        {
            DBS = dBS;
            DataColumns = new List<string>(); 
            DataColumns.Add("NumberTeamStatistic");
            DataColumns.Add("GameNumber");
            DataColumns.Add("TeamName");
            DataColumns.Add("MatchResult");
            DataColumns.Add("GoalsFor");
            DataColumns.Add("GoalsAgainst");
            DataColumns.Add("ShotsFor");
            DataColumns.Add("ShotsAgainst");
            ObjectList = DBS.ToList<object>();
        }

        new public DbSet<TeamStatistic>? DBS { get; set; }
    }
}
