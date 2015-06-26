<?xml version='1.0' encoding='UTF-8'?>
<Library LVVersion="12008004">
	<Property Name="NI.Lib.Icon" Type="Bin">%A#!"!!!!!)!"1!&amp;!!!-!%!!!@````]!!!!"!!%!!!(]!!!*Q(C=\&gt;8"=&gt;MQ%!8143;(8.6"2CVM#WJ",7Q,SN&amp;(N&lt;!NK!7VM#WI"&lt;8A0$%94UZ2$P%E"Y.?G@I%A7=11U&gt;M\7P%FXB^VL\`NHV=@X&lt;^39O0^N(_&lt;8NZOEH@@=^_CM?,3)VK63LD-&gt;8LS%=_]J'0@/1N&lt;XH,7^\SFJ?]Z#5P?=F,HP+5JTTF+5`Z&gt;MB$(P+1)YX*RU2DU$(![)Q3YW.YBG&gt;YBM@8'*\B':\B'2Z&gt;9HC':XC':XD=&amp;M-T0--T0-.DK%USWS(H'2\$2`-U4`-U4`/9-JKH!&gt;JE&lt;?!W#%;UC_WE?:KH?:R']T20]T20]\A=T&gt;-]T&gt;-]T?/7&lt;66[UTQ//9^BIHC+JXC+JXA-(=640-640-6DOCC?YCG)-G%:(#(+4;6$_6)]R?.8&amp;%`R&amp;%`R&amp;)^,WR/K&lt;75?GM=BZUG?Z%G?Z%E?1U4S*%`S*%`S'$;3*XG3*XG3RV320-G40!G3*D6^J-(3D;F4#J,(T\:&lt;=HN+P5FS/S,7ZIWV+7.NNFC&lt;+.&lt;GC0819TX-7!]JVO,(7N29CR6L%7,^=&lt;(1M4#R*IFV][.DX(X?V&amp;6&gt;V&amp;G&gt;V&amp;%&gt;V&amp;\N(L@_Z9\X_TVONVN=L^?Y8#ZR0J`D&gt;$L&amp;]8C-Q_%1_`U_&gt;LP&gt;WWPAG_0NB@$TP@4C`%`KH@[8`A@PRPA=PYZLD8Y!#/7SO!!!!!!</Property>
	<Property Name="NI.Lib.SourceVersion" Type="Int">302022660</Property>
	<Property Name="NI.Lib.Version" Type="Str">1.0.0.0</Property>
	<Item Name="encoder" Type="Folder">
		<Item Name="Decoder.vi" Type="VI" URL="../encoder/Decoder.vi"/>
		<Item Name="Encode.vi" Type="VI" URL="../encoder/Encode.vi"/>
	</Item>
	<Item Name="express" Type="Folder">
		<Item Name="ConfigAuto.vi" Type="VI" URL="../_express/ConfigAuto.vi"/>
	</Item>
	<Item Name="interface" Type="Folder">
		<Item Name="CThread" Type="Folder">
			<Item Name="RecorderMainCThread.vi" Type="VI" URL="../interface/CThread/RecorderMainCThread.vi"/>
		</Item>
		<Item Name="ConfigurePacketReader.vi" Type="VI" URL="../interface/ConfigurePacketReader.vi"/>
		<Item Name="ConfigurePacketWriter.vi" Type="VI" URL="../interface/ConfigurePacketWriter.vi"/>
		<Item Name="Packet Recorder Mode.vi" Type="VI" URL="../interface/Packet Recorder Mode.vi"/>
		<Item Name="RecorderMainLoop.vi" Type="VI" URL="../interface/RecorderMainLoop.vi"/>
		<Item Name="RecorderMainNoLoop.vi" Type="VI" URL="../interface/RecorderMainNoLoop.vi"/>
	</Item>
	<Item Name="reader" Type="Folder">
		<Item Name="ReaderClose.vi" Type="VI" URL="../reader/ReaderClose.vi"/>
		<Item Name="ReaderCore.vi" Type="VI" URL="../reader/ReaderCore.vi"/>
		<Item Name="ReadHeader.vi" Type="VI" URL="../reader/ReadHeader.vi"/>
		<Item Name="ReadSelectivePacket.vi" Type="VI" URL="../reader/ReadSelectivePacket.vi"/>
	</Item>
	<Item Name="vars" Type="Folder">
		<Item Name="ButtonPacketSize.vi" Type="VI" URL="../vars/ButtonPacketSize.vi"/>
		<Item Name="RemoteConf.vi" Type="VI" URL="../vars/RemoteConf.vi"/>
		<Item Name="SystemMode.vi" Type="VI" URL="../vars/SystemMode.vi"/>
	</Item>
	<Item Name="writer" Type="Folder">
		<Item Name="WriteCustomCall.vi" Type="VI" URL="../writer/WriteCustomCall.vi"/>
		<Item Name="WriteHeader.vi" Type="VI" URL="../writer/WriteHeader.vi"/>
		<Item Name="WriterClose.vi" Type="VI" URL="../writer/WriterClose.vi"/>
		<Item Name="WriterCore.vi" Type="VI" URL="../writer/WriterCore.vi"/>
		<Item Name="WriteSelectivePacket.vi" Type="VI" URL="../writer/WriteSelectivePacket.vi"/>
	</Item>
	<Item Name="ConfigData.ctl" Type="VI" URL="../ConfigData.ctl"/>
</Library>
