name="aura";
version=1;
tables={tableName="aurasTable",tableIndex=9527};
function PrintMe()
    print("This is print me");
end;

function tick()
    if readKeyState("w") then
        --print(" key w pressed"); 
        setNowNumber(1);
    else
       --print("wait key press");  
    end;
end;
