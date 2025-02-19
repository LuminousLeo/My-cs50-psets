//part 1: multiple choices
document.addEventListener('DOMContentLoaded', function() {
    //if correct button was clicked
    let correct1 = document.querySelector('.correct1');
    correct1.addEventListener('click', function() {
        //turn button to green and print correct underneath
        correct1.style.backgroundColor = 'green';
        document.querySelector('#feedback1').innerHTML = 'Correct:)';
    });
        //if the incorrect button was clicked
        let incorrects1 = document.querySelectorAll('.incorrect1');
        //go to the incorrect button in question
        for (let i = 0; i < incorrects1.length; i++) {
            incorrects1[i].addEventListener('click', function() {
                //turn it to red and print incorrect underneath it
                incorrects1[i].style.backgroundColor = 'red';
                document.querySelector('#feedback1').innerHTML = 'Incorrect:(';
            });
        }

        //part2: free response
        //for when the button is clicked
        document.querySelector('#check1').addEventListener('click', function() {
            //get the value of the input field
            let input1 = document.querySelector('#input1').value;
            let midland = 'midland';
            let compare1 = midland.localeCompare(input1, 'en', {sensitivity: 'base', ignorePunctuation: true});
            //if it is midland
            if (compare1 === 0) {
                //turn button to green and print correct underneath
                document.querySelector('#input1').style.backgroundColor= 'green';
                document.querySelector('#feedback2').innerHTML = 'Correct:)';
            }
            //if not
            else {
                //turn it to red and print incorrect underneath it
                document.querySelector('#input1').style.backgroundColor = 'red';
                document.querySelector('#feedback2').innerHTML = 'Incorrect:(';
            }
        });

        //if correct button was clicked
        let correct2 = document.querySelector('.correct2');
        correct2.addEventListener('click', function() {
            //turn button to green and print correct underneath
            correct2.style.backgroundColor = 'green';
            document.querySelector('#feedback3').innerHTML = 'Correct:)';
        });
            //if the incorrect button was clicked
            let incorrects2 = document.querySelectorAll('.incorrect2');
            //go to the incorrect button in question
            for (let i = 0; i < incorrects2.length; i++) {
                incorrects2[i].addEventListener('click', function() {
                    //turn it to red and print incorrect underneath it
                    incorrects2[i].style.backgroundColor = 'red';
                    document.querySelector('#feedback3').innerHTML = 'Incorrect:(';
                });
            }
            document.querySelector('#check2').addEventListener('click', function() {
                //get the value of the input field
                let input2 = document.querySelector('#input2').value;
                let band_of_the_hawk = 'band of the hawk';
                let compare2 = band_of_the_hawk.localeCompare(input2, 'en', {sensitivity: 'base', ignorePunctuation: true});
                //if it is griffith
                if (compare2 === 0) {
                    //turn button to green and print correct underneath
                    document.querySelector('#input2').style.backgroundColor= 'green';
                    document.querySelector('#feedback4').innerHTML = 'Correct:)';
                }
                //if not
                else {
                    //turn it to red and print incorrect underneath it
                    document.querySelector('#input2').style.backgroundColor = 'red';
                    document.querySelector('#feedback4').innerHTML = 'Incorrect:(';
                }
            });

});