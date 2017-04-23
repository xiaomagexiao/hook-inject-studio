package com.example.mama.readmemory;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

/**
 * Created by mama on 2017/4/15.
 */

public class ScanMemoryTest extends Activity implements View.OnClickListener {

    private EditText et_search_value;
    private Button bt_start;
    private Button bt_bigger;
    private Button bt_equal;
    private Button bt_smaller;
    private Button bt_restart;
    private Button bt_change;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_memory_test);

        initView();
        setListener();
        NativeSearchHelper.initso();
    }

    private void setListener() {
        this.bt_start.setOnClickListener(this);
        this.bt_bigger.setOnClickListener(this);
        this.bt_smaller.setOnClickListener(this);
        this.bt_equal.setOnClickListener(this);
        this.bt_restart.setOnClickListener(this);
        this.bt_change.setOnClickListener(this);
    }

    private void initView() {
        this.et_search_value = (EditText) this.findViewById(R.id.search_value);
        this.bt_start = (Button) this.findViewById(R.id.start);
        this.bt_bigger = (Button) this.findViewById(R.id.bigger);
        this.bt_smaller = (Button) this.findViewById(R.id.smaller);
        this.bt_equal = (Button) this.findViewById(R.id.equal);
        this.bt_restart = (Button) this.findViewById(R.id.restart);
        this.bt_change = (Button) this.findViewById(R.id.change);
    }

    @Override
    public void onClick(View view) {
        int i = view.getId();
        if (i == R.id.start) {
            NativeSearchHelper.init(Long.valueOf(this.et_search_value.getText().toString()));

        } else if (i == R.id.bigger) {
            NativeSearchHelper.bigger();

        } else if (i == R.id.smaller) {
            NativeSearchHelper.smaller();

        } else if (i == R.id.equal) {
            NativeSearchHelper.equal();

        } else if (i == R.id.restart) {
            NativeSearchHelper.clear();

        } else if (i == R.id.change) {
            NativeSearchHelper.newValue(Long.valueOf(this.et_search_value.getText().toString()));

        }
    }
}
