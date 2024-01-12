BEGIN{
	print "The latest field of users and shells"
	print "User\t\t\t\t\tHome Directory\t\t\t\t\tShell"
	print "----\t\t\t\t\t--------------\t\t\t\t\t-----"
	FS=":"
}
{
	print $1"\t\t\t\t\t"$6"\t\t\t\t\t"$7
}
END{
	print "This is the conclusion"
}




	
