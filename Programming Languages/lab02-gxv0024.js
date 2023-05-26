
//Name: George Vo
//ID: 1001360024
//Due Date: October 21st, 2021
console.log("Name: George Vo")
console.log("ID: 1001360024")
console.log("Due Date: October 21st, 2021")
console.log("Number 1") //Prints out question separator
var inputable = [1,2,3,4,5,6,7,8,9,10] //Creates an Array from 1-10
console.log(inputable) //Prints out the inputable table.
console.log("Number 2a") //Prints out question separator
var fivetable = inputable
var fiveTable = inputable.map(function(x){return x*5}) //Multiplies all elements in the array by 5
console.log(fiveTable) //Prints out the result of fiveTable
console.log("Number 2b") //Prints out question separator
var thirteenTable = inputable.map(function(x){return x*13}) //Multiplies all elements in the array by 13
console.log(thirteenTable) //Prints out the result of thirteenTable
console.log("Number 2c") //Prints out question separator
var squaresTable = inputable.map(function(x){return x*x}) //Squares each element in the array
console.log(squaresTable) //Prints out the results of squaresTable
console.log("Number 3") //Prints out question separator
var oddMultiples = inputable.map(function(x){return (x*10)-5}) //Transforms array by multiplying by 10 then subtracting by 5, which results in odd multiples of 5 up to 100
console.log(oddMultiples) //Prints out results of oddMultiples
console.log("Number 4") //Prints out question separator
sevenGenerator = function(start,end,sum){
	if(start>end)
		return sum
	if(start%2==0)
		sum = sum + start
	return sevenGenerator(start+7,end,sum)
}
console.log(sevenGenerator(0,100,0))
console.log("Number 5a") //Prints out question separator
function cylinder_volume(r) //Currying process
{
	return(h)=> {
		return r*r*h*3.14
	}
}
console.log(cylinder_volume(5)(10)) //Prints out volume for radius = 5 and height = 10
console.log("Number 5b") //Prints out question separator
console.log(cylinder_volume(5)(17)) //Prints out volume for radius = 5 and height = 17
console.log("Number 5c") //Prints out question separator
console.log(cylinder_volume(5)(11)) //Prints out volume for radius = 5 and height = 11
console.log("Number 6") //Prints out question separator
makeTag = function(beginTag,endTag){ //function given in assignment
	return function(textcontent){ //function given in assignment
		return beginTag+textcontent+endTag //function given in assignment
	} //function given in assignment
} //function given in assignment
 //added spaces to make visualizing it easier
first = makeTag("  <th>","</th>\n")("George") //input for first name 1
last = makeTag("  <th>","</th>\n")("Vo") //input for last name 1
age = makeTag("  <th>","</th>\n")("21") //input for age 1
first2 = makeTag("  <th>","</th>\n")("Joe") //input for first name 2
last2 = makeTag("  <th>","</th>\n")("Nguyen") //input for last name 2
age2 = makeTag("  <th>","</th>\n")("23") //input for age 2
full = makeTag(" <tr>\n"," </tr>\n")(first+last+age) //group 1st set of first name, last name, and age
full2 = makeTag(" <tr>\n"," </tr>\n")(first2+last2+age2) //group 2nd set of first name, last name, and age
console.log(makeTag("<table>\n","</table>")(full+full2)) //group 1st set and 2nd set between table. Prints the result.
console.log("Question 8") //Prints out question separator
console. log("Extra credit was not attempted") //Prints out my attempt at extra credit