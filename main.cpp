void Board()
{
    for(int i =0;i < HEIGHT; i++){
        cout << "\t\t#";
        for(int j = 0;j < WIDTH -2;j++){
            if(i==0||i==HEIGHT-1){
                cout<<'#';
            }
            else if(i==y && j==x) cout<<'0';
            else cout << " ";
        }
        cout<<"#\n";
    }
}
