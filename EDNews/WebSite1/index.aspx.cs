using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class index : System.Web.UI.Page
{
    public string pics;
    public string texts;
    public string links;

    protected void Page_Load(object sender, EventArgs e)
    {
        News.getPics(ref pics, ref texts, ref links);
        gvNews.DataSource = SqlHelper.excuteDataSet("select * from t_news order by addTime DESC");
        gvNews.DataBind();
    }
}