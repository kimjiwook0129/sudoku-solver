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
<<<<<<< HEAD
			fail: function (error) {}
=======
			fail: function (error) {
				;
			}
>>>>>>> 8a8e5f09ad5903eb2e264f9175631b5c5fc2070c
		});


// assign the new values to the numbers (string)


	});
});

