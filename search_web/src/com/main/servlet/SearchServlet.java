package com.main.servlet;


import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Created by mama on 2017/4/23.
 */
public class SearchServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doPost(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {


        String value = req.getParameter("cmd");

        execute("adb shell am broadcast -a inject.cmd --es cmd " + value);
    }

    private String execute(String cmd) {
        cmd = cmd.replace("\"","'");
        logInfo("cmd info: " + cmd);
        CmdUtils.exeCmd(cmd);
        return "";

    }

    private void logInfo(String info) {
        System.out.println(info);
    }
}
