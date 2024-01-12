param (
	[string]$targetIP = "192.168.20.5",
	[int]$targetPort = 7007
)

function Send-TcpPacket {
	param(
		[string]$destination,
		[int]$port
	)
	
	$tcpClient = New-Object System.Net.Sockets.TcpClient
	$tcpClient.Connect($destination, $port)
	$tcpClient.Close()
}

while ($true) {
	Send-TcpPacket -destination $targetIP -port $targetPort
	Write-Host "TCP packet sent to $targetIP $targetPort"
	
	#wait for 1 minute
	
	Start-Sleep -Seconds 60
}
