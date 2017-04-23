package com.example.dex.ui;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import com.example.dex.target.R;
import com.example.mama.readmemory.ScanMemoryTest;


public class MainActivity extends Activity {
    public static Context context;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.setContentView(R.layout.activity_main);
        context = this;
        Say.show();
        findViewById(R.id.execute).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                MainActivity.this.sendBroadcast(new Intent(Say.intentAction));
            }
        }); findViewById(R.id.scan_memory).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MainActivity.this, ScanMemoryTest.class));
            }
        });
    }

}
