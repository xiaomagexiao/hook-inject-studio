<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>内存搜索</title>
    <script type="application/javascript" src="js/jquery-1.9.1.min.js"></script>

    <script type="application/javascript">
        function request(cmd) {
            $.post("/search", {cmd: cmd}, function (data) {
//                alert(data);
            });
        }
        function initValue() {
            var cmd = '{"action":"init"--"value":"' + $("#say").val() + '"}';
            request(cmd);
        }
        function requestWithoutValue(type) {
            request('{"action":"' + type + '"}');
        }
        function newValue() {
            var cmd = '{"action":"newValue"--"value":"' + $("#say").val() + '"}';
            request(cmd);
        }

        function setValue() {
            var list = $("#address").val();
            var arr = list.split("\n");
            for (var i = 0; i < arr.length; i++) {
                console.log(i + ":" + arr[i]);
                var address = arr[i].replace("address:", "").trim();
                if (address.indexOf("->") >= 0) {
                    address = address.substring(0, address.indexOf("->")).trim();
                }
                console.log(address);
                var cmd = '{"action":"setValue"--"value":"' + $("#new_value").val() + '"--"address":"' + address + '"}';
                request(cmd);
            }
        }
    </script>

</head>
<body>
模仿ce搜索内容：<br/>

<table>
    <tr>
        <td><input type=" text" id="say" placeholder="输入搜索的内容"></td>
        <td>
            <input onclick="initValue()" type="button" value="初始化" style="width: 150px;line-height: 50px;"><br/>
            <input onclick="newValue()" type="button" value="变更为" style="width: 150px;line-height: 50px;"><br/>
            <input onclick="requestWithoutValue('bigger');" type="button" value="变大"
                   style="width: 150px;line-height: 50px;"><br/>
            <input onclick="requestWithoutValue('smaller');" type="button" value="变小"
                   style="width: 150px;line-height: 50px;"><br/>
            <input onclick="requestWithoutValue('equal');" type="button" value="不变"
                   style="width: 150px;line-height: 50px;"><br/>
            <input onclick="requestWithoutValue('clear');" type="button" value="清空"
                   style="width: 150px;line-height: 50px;"><br/>
            <input onclick="requestWithoutValue('printResult');" type="button" value="显示结果"
                   style="width: 150px;line-height: 50px;"><br/>
        </td>
    </tr>
    <tr>
        <td colspan="2">
            <br/><br/>
            0X<textarea id="address" placeholder="修改值的地址" rows="8"></textarea>
            -> <input type=" text" id="new_value" placeholder="新值">
            <input type="button" onclick="setValue()" value="给地址设置值">
        </td>
    </tr>
</table>
</body>

</html>
