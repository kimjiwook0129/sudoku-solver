i$(document).ready(function() {



	$("#solve").click(function(e){
		e.preventDefault();

		let numbers = "";
		for (let i = 0; i < 81; ++i) {
			if (document.getElementById(i.toString()).value != "") {
				numbers += document.getElementById(i.toString()).value;
			} else {
				numbers += '0';
			}
		}

		$.ajax({
			type: 'get',
			dataType: 'json',
			data: {Nums: numbers},
			url: '/solve',
			success: function (data) {
				let stringdata = data.toString();
				console.log(stringdata);
				for (let index = 0; index < 81; ++index) {
					document.getElementById(index.toString()).value = stringdata[index];
				}
			},
			fail: function (error) {
				;
			}
		});


// assign the new values to the numbers (string)


	});
});

