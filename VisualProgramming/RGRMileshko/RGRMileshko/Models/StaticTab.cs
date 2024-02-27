using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;

namespace RGRMileshko.Models
{
    public class StaticTab : MyTab
    {
        public StaticTab(string h = "", List<string>? dc = null) : base(h, dc)
        {
            ButtonVisible = false;
        }
        public DbSet<object>? DBS { get; set; }
    }
}
