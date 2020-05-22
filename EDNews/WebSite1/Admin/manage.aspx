<%@ Page Language="C#" AutoEventWireup="true" CodeFile="manage.aspx.cs" Inherits="admin_manage" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title>后台管理主页面</title>
    <link href="../css/style.css" rel="stylesheet" />
</head>
<body>
    <form id="form1" runat="server">
        <div id="box">
            <div id="adminHeader">
                <div style="float:left"><asp:Label ID="lblUser" runat="server"></asp:Label></div>
                <div style="float:right">
                    <asp:Button ID="btnExit" runat="server" Text="退出系统" OnClick="btnExit_Click" /></div>
            </div>
            <div class="splitDiv"></div>
            <div id="adminMenu">

                <asp:Button ID="btnAddNews" runat="server" OnClick="btnAddNews_Click" Text="发布信息" />
&nbsp;&nbsp;
                <asp:Button ID="btnManageLanMu" runat="server" Text="栏目管理" />

            </div>
            <div class="splitDiv"></div>
            <div id="adminContent">
                <asp:GridView ID="gvNews" runat="server" AutoGenerateColumns="False" CellPadding="4" ForeColor="#333333" GridLines="None" Width="1000px">
                    <AlternatingRowStyle BackColor="White" />
                    <Columns>
                        <asp:BoundField DataField="newid" HeaderText="编号">
                        <ItemStyle HorizontalAlign="Center" Width="50px" />
                        </asp:BoundField>
                        <asp:HyperLinkField DataNavigateUrlFields="newid" DataNavigateUrlFormatString="../shownews.aspx?id={0}" DataTextField="title" HeaderText="新闻标题" Target="_blank" />
                        <asp:BoundField DataField="userName" HeaderText="发布者">
                        <ItemStyle HorizontalAlign="Center" Width="60px" />
                        </asp:BoundField>
                        <asp:BoundField DataField="lanMuName" HeaderText="栏目">
                        <ItemStyle HorizontalAlign="Center" Width="60px" />
                        </asp:BoundField>
                        <asp:BoundField DataField="hitCount" HeaderText="点击数">
                        <ItemStyle HorizontalAlign="Center" Width="60px" />
                        </asp:BoundField>
                        <asp:BoundField DataField="addTime" HeaderText="发布时间">
                        <ItemStyle HorizontalAlign="Center" Width="160px" />
                        </asp:BoundField>
                        <asp:TemplateField HeaderText="修改">
                            <ItemTemplate>
                                <asp:LinkButton ID="lbtnEditNews" runat="server" OnClick="lbtnEditNews_Click">编辑</asp:LinkButton>
                                &nbsp;<asp:LinkButton ID="lbtnDelNews" runat="server" OnClick="lbtnDelNews_Click">删除</asp:LinkButton>
                            </ItemTemplate>
                            <ItemStyle HorizontalAlign="Center" Width="110px" />
                        </asp:TemplateField>
                    </Columns>
                    <EditRowStyle BackColor="#2461BF" />
                    <FooterStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
                    <HeaderStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
                    <PagerStyle BackColor="#2461BF" ForeColor="White" HorizontalAlign="Center" />
                    <RowStyle BackColor="#EFF3FB" />
                    <SelectedRowStyle BackColor="#D1DDF1" Font-Bold="True" ForeColor="#333333" />
                    <SortedAscendingCellStyle BackColor="#F5F7FB" />
                    <SortedAscendingHeaderStyle BackColor="#6D95E1" />
                    <SortedDescendingCellStyle BackColor="#E9EBEF" />
                    <SortedDescendingHeaderStyle BackColor="#4870BE" />
                </asp:GridView>
            </div>
        </div>
    </form>
</body>
</html>
