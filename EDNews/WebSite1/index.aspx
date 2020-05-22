<%@ Page Language="C#" AutoEventWireup="true" CodeFile="index.aspx.cs" Inherits="index" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title>欢迎访问EDNews新闻网</title>
    <link href="css/style.css" rel="stylesheet" />
</head>
<body>
    <form id="form1" runat="server">
        <div id="box">
            <div id="header"></div>
            <div class="splitDiv"></div>
            <div id="main">
                <div id="left">
                     <script type="text/javascript" language="JavaScript">        
                        var focus_width=490
                        var focus_height=280
                        var text_height=20
                        var swf_height = focus_height+text_height
                        var pics = "<%=pics %>";
                        var links = "<%=links %>";
                        var texts = "<%=texts %>";
                        document.write('<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0" width="'+ focus_width +'" height="'+ swf_height +'">');
                        document.write('<param name="allowScriptAccess" value="sameDomain"><param name="movie" value="images/playswf.swf"><param name="quality" value="high"><param name="bgcolor" value="#FFFFFF">');
                        document.write('<param name="menu" value="false"/><param name=wmode value="opaque"/>');
                        document.write('<param name="FlashVars" value="pics='+pics+'&links='+links+'&texts='+texts+'&borderwidth='+focus_width+'&borderheight='+focus_height+'&textheight='+text_height+'">');
                        document.write('<embed src="images/playswf.swf" wmode="opaque" FlashVars="pics='+pics+'&links='+links+'&texts='+texts+'&borderwidth='+focus_width+'&borderheight='+focus_height+'&textheight='+text_height+'" menu="false" bgcolor="#FFFFFF" quality="high" width="'+ focus_width +'" height="'+ swf_height +'" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" />');
                        document.write('</object>');       
                      </script> 
                </div>
                <div id="right">
                    <asp:GridView ID="gvNews" runat="server" AutoGenerateColumns="False" ShowHeader="False">
                        <Columns>
                            <asp:HyperLinkField DataNavigateUrlFormatString="shownews.aspx?id={0}" DataTextField="title" DataNavigateUrlFields="newid" Target="_blank">
                            <ItemStyle Width="420px" />
                            </asp:HyperLinkField>
                            <asp:BoundField DataField="addTime" DataFormatString="{0:[yy-MM-dd]}">
                            <ItemStyle Width="80px" HorizontalAlign="Right" />
                            </asp:BoundField>
                        </Columns>
                    </asp:GridView>
                </div>
            </div>
            <div class="splitDiv"></div>
            <div id="footer">[<a href="admin/index.aspx" target="_blank">后台管理</a>]</div>
        </div>
    </form>
</body>
</html>
