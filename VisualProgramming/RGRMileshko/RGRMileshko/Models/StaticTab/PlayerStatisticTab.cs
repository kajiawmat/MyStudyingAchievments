using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using RGRMileshko.Models.Database;
using System.Linq;

namespace RGRMileshko.Models.StaticTabs
{
    public class PlayerStatisticTab : StaticTab
    {
        public PlayerStatisticTab(string h = "", DbSet<PlayerStatistic>? dBS = null) : base(h)
        {
            DBS = dBS;
            DataColumns = new List<string>();
            DataColumns.Add("NumberPlayerStatistic");
            DataColumns.Add("GameNumber");
            DataColumns.Add("PlayerName");
            DataColumns.Add("Goals");
            DataColumns.Add("ShotsAttempted");
            DataColumns.Add("CorsiFor");
            DataColumns.Add("CorsiAgainst");
            DataColumns.Add("Takeaways");
            DataColumns.Add("Giveaways");
            DataColumns.Add("Deleting");
            ObjectList = DBS.ToList<object>();
            ObjectList.Add(false);
        }

        new public DbSet<PlayerStatistic>? DBS { get; set; }
    }
}
