var myApp = angular.module('mainapp', []);
myApp.controller("mainController", function($scope,$http){
	var dataList;
	$http.get("/datalist").success(
		function(data){
			$scope.fileList=data.files;
			dataList=data.files;
			console.log(data.files[0]);
			g2 = new Dygraph(
    			document.getElementById("graphdiv2"),
   		 		"data/"+data.files[0], // path to CSV file
    			{ylabel:'Deflection Angle',
	 			xlabel:'Sample Number',
				 animatedZooms:true}          // options
  			);

		}
	);

	$scope.switchGraph=function(index){
		console.log(index);
		g2 = new Dygraph(
    			document.getElementById("graphdiv2"),
   		 		"data/"+$scope.fileList[index], // path to CSV file
    			{ylabel:'Deflection Angle',
	 			xlabel:'Sample Number',
				 animatedZooms:true}          // options
  			);

	}

});
