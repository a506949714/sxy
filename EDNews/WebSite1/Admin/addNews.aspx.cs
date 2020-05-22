using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class admin_addNews : System.Web.UI.Page
{
    Users u;
    protected void Page_Load(object sender, EventArgs e)
    {
        if(Session["user"]==null)
        {
            Response.Redirect("index.aspx");
        }
        else
        {
            u = (Users)Session["user"];
        }
        ddlLanMu.DataSource = News.getLanMuList();
        ddlLanMu.DataTextField = "lanMuName";
        ddlLanMu.DataValueField = "lanMuId";
        ddlLanMu.DataBind();
    }

    protected void Button1_Click(object sender, EventArgs e)
    {
        News n = new News();
        n.title = txtTitle.Text;
        n.contents = content1.Value;
        n.addTime = DateTime.Now;
        n.hitCount = 0;
        n.lanMuId = Convert.ToInt32(ddlLanMu.SelectedValue);
        n.uid = u.uid;
        n.img = txtImgUrl.Text;
        if(News.addNews(n)==true)
        {
            Response.Write("<script>alert('发布成功！')</script>");
        }
        else 
        {
            Response.Write("<script>alert('发布失败！')</script>");
        }
    }
}