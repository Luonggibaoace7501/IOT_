const firebaseConfig = {
  apiKey: "AIzaSyDzfkvZgarglFlXwdrV3l4Yy8V7_ZC0cso",
  authDomain: "do-muc-nuoc.firebaseapp.com",
  databaseURL: "https://do-muc-nuoc-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "do-muc-nuoc",
  storageBucket: "do-muc-nuoc.appspot.com",
  messagingSenderId: "515424281555",
  appId: "1:515424281555:web:0b2ab7b8e3f2c59c7a8526",
  measurementId: "G-SB7Z2GXS1L"
};
    firebase.initializeApp(firebaseConfig);
    firebase.analytics();
    
     var cao = document.getElementById('cao');
     var thetich = document.getElementById('thetich');
     var dbRef = firebase.database().ref("muc_nuoc").child('cao');
     dbRef.on('value', snap => cao.innerHTML = snap.val() + " cm");
     var dbRef = firebase.database().ref("muc_nuoc").child('thetich');
     dbRef.on('value', snap => thetich.innerHTML = snap.val() + " cm^3");
  //----------------------------------------------
    

    


     var btnOn = document.getElementById("btnOnId_01");
     var btnOff = document.getElementById("btnOffId_01");
  
     btnOn.onclick = function(){
      firebase.database().ref("/muc_nuoc").update({
      "led": 1 
  
     });
     }
     btnOff.onclick = function(){
      firebase.database().ref("/muc_nuoc").update({
      "led" : 0
     });
     }
     firebase.database().ref("/muc_nuoc/led").on("value", function(snapshot){
      var ss = snapshot.val();
      if (ss==1){
      document.getElementById("denId_01").src = "./hinhanh/sang.png";
    }
      else{
      document.getElementById ("denId_01").src="hinhanh/tat.png"
    }
    
     });
  //------------------------------------------------------------
     var bon1 = document.getElementById("bon_01");
     var bon2 = document.getElementById("bon_02");
     var bon1 = document.getElementById("bon_03");
  
     bon1 = function(){
      firebase.database().ref("/muc_nuoc").update({
      "bon": 1 
     });
    }
     bon2 = function(){
      firebase.database().ref("/muc_nuoc").update({
      "bon" : 2
     });
     }
     bon3 = function(){
      firebase.database().ref("/muc_nuoc").update({
      "bon": 3 
     });
     }
     firebase.database().ref("/muc_nuoc/bon").on("value", function(snapshot){
      var s = snapshot.val();
      if (s==1){
      document.getElementById("bon_01").src = "./hinhanh/bonthap.png";
    }
      if (s==2){
      document.getElementById("bon_01").src = "./hinhanh/bon1.png";
    }
    if (s==3){
      document.getElementById("bon_01").src = "./hinhanh/boncao.png";
    }
    
     });
       
    