using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RGRMileshko.Models
{
    public class DynamicTab : MyTab
    {
        public DynamicTab(string h = "", List<object>? db = null, List<string>? dc = null) : base(h, dc)
        {
            ButtonVisible = true;
            ObjectList = db;
        }
        public Query BindedQuery { get; set; }
    }
}
