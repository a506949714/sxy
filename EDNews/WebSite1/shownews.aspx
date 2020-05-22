<%@ Page Language="C#" AutoEventWireup="true" CodeFile="shownews.aspx.cs" Inherits="shownews" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title>查看新闻页面</title>
    <link href="css/style.css" rel="stylesheet" />
</head>
<body>
    <form id="form1" runat="server">
        <div id="box">
            <div id="header"></div>
            <div class="splitDiv"></div>
            <div id="main">
                <div id="newsTitle">
                    <asp:Label ID="lblTitle" runat="server"></asp:Label>
                </div>
                <div class="line"></div>
                <div id="newsInfo">
                    <asp:Label ID="lblAddTime" runat="server"></asp:Label>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                    <asp:Label ID="lblHitCount" runat="server"></asp:Label>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                    <asp:Label ID="lblAuthor" runat="server"></asp:Label>
                </div>
                <div id="newsContent">
                    <asp:Label ID="lblContent" runat="server"></asp:Label>
                </div>
            </div>
            <div class="splitDiv"></div>
            <div id="footer">[<a href="admin/index.aspx" target="_blank">后台管理</a>]</div>
        </div>
    </form>
</body>
</html>
