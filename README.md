<h1>MIMO OFDM  Block Diagram C Modeling and Simulation </h1>	
<div style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;">
<table width="600px" border="1" cellpadding="2" cellspacing="2" style="background-color: #ffffff;">
<tr valign="top">
<td style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"> <a href="https://www.ccdsp.org/"><img src="sd-logo-tm_sm.png" width="104" height="109" alt="sdsp logo" title="" /></a>
</span></p>
</td>
<td style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"><a href="#linux_tux"><img src="images/Tux.svg.png" width="62" height="74" alt="Linux Tux" title="" /></a> <!-- width="250" height="297" -->Developed on Linux.
</span></p>
</td>
</tr>
</table>
</div>
<p>
Icons <img src="images/noun-links-821764.png" width="30" height="30" alt="link github" title="" />and<img src="images/noun-tools-4827171.png" width="40" height="40" alt="link building" title="" />Credit the  <a href="https://thenounproject.com/">Noun Project</a>.
<p>
<div style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;">
<table  width="100%" style="border: 2px solid #000000; border-collapse: collapse" cellspacing="0" cellpadding="0">	
<tr valign="top">
<td width="40" height="15" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: bold; color: #000000; background-color: transparent; text-decoration: none;">Item</span></p>
</td>
<td width="293" height="15" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: bold; color: #000000; background-color: transparent; text-decoration: none;">Description</span><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"> </span></p>
</td>
<td width="73" height="15" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: bold; color: #000000; background-color: transparent; text-decoration: none;">Link</span></p>
</td>
<td width="134" height="15" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: bold; color: #000000; background-color: transparent; text-decoration: none;">Type</span></p>
</td>
</tr>
<tr valign="top">
<td width="40" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">1</span></p>
</td>
<td width="293" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">Introduction to the Capsim&reg; MIMO OFDM Block Diagram Modeling and Simulation</span></p>
</td>
<td width="73" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"><a href="#introduction"><img src="images/noun-links-821764.png" width="30" height="30" alt="link" title="" /></a></span></p>
</td>
<td width="134" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">Introduction</span></p>
</td>
</tr>
<tr valign="top">
  <td style="border-width : 0px;">2</td>
  <td style="border-width : 0px;"><p align="center"><strong>Computing the  Singular Value Decomposition (SVD) with Fixed Point CORDIC Operations</strong></p>
    <p align="center">Application to MIMO-OFDM<strong></strong></p></td>
  <td style="border-width : 0px;"><a href="Paper/MIMO-OFDM_SVD_CORDIC_Operations.pdf"><img src="images/pdf.gif" width="22" height="21" alt=""/></a></td>
  <td style="border-width : 0px;">Paper and Latex File</td>
</tr>
<tr valign="top">
<td width="40" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style="font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">3</span></p>
</td>
<td width="293" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"> Capsim&reg; Block Diagram MIMO OFDM With Channel Model, Noise and Demodulation of Streams.</span></p>
</td>
<td width="73" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"><a href="#mimo-ofdm"><img src="images/noun-links-821764.png" width="30" height="30" alt="link" title="" /></a></span></p>
</td>
<td width="134" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">Screen Shots</span></p>
</td>
</tr>
<tr valign="top">
  <td style="border-width : 0px;">4</td>
  <td style="border-width : 0px;">Results of Block Diagram Simulations Floating Point (LAPACK) versus Fixed Point CORDIC 2x2 SVD Beam Forming MIMO-OFDM</td>
  <td style="border-width : 0px;"><a href="#results-fxp-floating-point"results-fxp-floating-point""><img src="images/noun-links-821764.png" width="30" height="30" alt="link" title="" /></a></td>
  <td style="border-width : 0px;">Analysis</td>
</tr>
<tr valign="top">
<td width="40" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style="font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">5</span></p>
</td>
<td width="293" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">List of Topologies Included in Repository</span>. See this <a href="#tops_list">link</a> for Block Diagrams for Various Topologies</p>
</td>
<td width="73" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"><a href="#tops_list"><img src="images/noun-links-821764.png" width="30" height="30" alt="link" title="" /></a></span></p>
</td>
<td width="134" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">Table</span></p>
</td>
</tr>
<tr valign="top">
  <td width="40" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style="font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">6</span></p>
  </td>
  <td width="293" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">List of OFDM, MIMO and Channel Model  C Blocks Included in Repository</span></p>
  </td>
  <td width="73" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"><a href="#block_list"><img src="images/noun-links-821764.png" width="30" height="30" alt="link" title="" /></a></span></p>
  </td>
  <td width="134" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">Table</span></p>
  </td>
</tr>
<tr valign="top">
<td width="40" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style="font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">7</span></p>
</td>
<td width="293" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">List of MIMO and Channel Model  C Subroutines Included in Repository</span></p>
</td>
<td width="73" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"><a href="#subs_table"><img src="images/noun-links-821764.png" width="30" height="30" alt="link" title="" /></a></span></p>
</td>
<td width="134" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">Table</span></p>
</td>
</tr>
<tr valign="top">
<td width="40" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style="font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">8</span></p>
</td>
<td width="293" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">Building Capsim&reg; for MIMO OFDM Modeling and Simulation </span></p>
</td>
<td width="73" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"><a href="#capsim_ofdm_instructions"><img src="images/noun-tools-4827171.png" width="40" height="40" alt="link building" title="" /></a></span></p>
</td>
<td width="134" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">Instructions</span></p>
</td>
</tr>
<tr valign="top">
<td width="40" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style="font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">9</span></p>
</td>
<td width="293" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">Capsim&reg; Text Mode Kernel (TMK) Installation </span></p>
</td>
<td width="73" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"><a href="https://github.com/silicondsp/capsim-tmk"><img src="images/github-mark.png" width="45" height="45" alt=""/></a></span></p>
</td>
<td width="134" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">GitHub Repository</span></p>
</td>
</tr>
<tr valign="top">
<td width="40" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style="font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">10</span></p>
</td>
<td width="293" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">GitHub Repository Capsim&reg; MIMO OFDM Block Diagram Modeling and Simulation</span></p>
</td>
<td width="73" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"><a href="https://github.com/silicondsp/ofdm-release"><img src="images/github-mark.png" width="45" height="45" alt="github"/></a></span></p>
</td>
<td width="134" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">GitHub Repository</span></p>
</td>
</tr>
<tr valign="top">
<td width="40" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style="font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">11</span></p>
</td>
<td width="293" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">GitHub Repository Capsim&reg;  OFDM Block Diagram Modeling and Simulation</span></p>
</td>
<td width="73" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"><a href="https://github.com/silicondsp/ofdm-release"><img src="images/github-mark.png" width="45" height="45" alt="github"/></a></span></p>
</td>
<td width="134" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">GitHub Repository</span></p>
</td>
</tr>		
<tr valign="top">
<td width="40" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style="font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">12</span></p>
</td>
<td width="293" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">OFDM Video Tutorials by Silicon DSP Corporation</span></p>
</td>
<td width="73" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"><a href="https://www.youtube.com/playlist?list=PLqL72R3p_ZYLOtQuAMUEziTbMKU4vdeHF"><img src="images/yt_logo_rgb_light-300x67.png" width="75" height="17" alt="youtube" title="" /></a></span></p>
</td>
<td width="134" style="border-width : 0px;"><p style=" text-align: left; text-indent: 0px; padding: 0px 0px 0px 0px; margin: 0px 0px 0px 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">Video Tutorial</span></p>
</td>
</tr>
<tr valign="top">
<td width="40" style="border-width : 0px;">13<br />
</td>
<td width="293" style="border-width : 0px;">MIMO OFDM <span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;"> Video Tutorials by Silicon DSP Corporation</span><br />
</td>
<td width="73" style="border-width : 0px;"><a href="https://www.youtube.com/playlist?list=PLqL72R3p_ZYLChzqSDrQGYKl_qvCaFW3U"><img src="images/yt_logo_rgb_light-300x67.png" width="75" height="17" alt="youtube" title="" /></a><br />
</td>
<td width="134" style="border-width : 0px;"><span style=" font-size: 10pt; font-family: 'Arial', 'Helvetica', sans-serif; font-style: normal; font-weight: normal; color: #000000; background-color: transparent; text-decoration: none;">Video Tutorial</span><br />
</td>
</tr>
		
<tr valign="top">
<td width="40" style="border-width : 0px;">14<br />
</td>
<td width="293" style="border-width : 0px;">Video Capsim Block Diagram Modeling MIMO-OFDM Open Loop 2x2 and 2x3 (must view for insights and better understanding of this Repository)<br />
</td>
<td width="73" style="border-width : 0px;"><a href="https://youtu.be/0Q2w50UiKec?list=PLqL72R3p_ZYIfjNC-m1Pu1j9MCIgjgr7T"><img src="images/yt_logo_rgb_light-300x67.png" width="75" height="17" alt="youtube" title="" /></a><br />
</td>
<td width="134" style="border-width : 0px;">Video Tutorial<br />
</td>
</tr>
<tr valign="top">
<td width="40" style="border-width : 0px;"><br />
</td>
<td width="293" style="border-width : 0px;"><br />
</td>
<td width="73" style="border-width : 0px;"><br />
</td>
<td width="134" style="border-width : 0px;"><br />
</td>
</tr>
</table>
<p>Note many blocks and subroutiunes used are described in the ofdm repository.<a href="https://github.com/silicondsp/ofdm-release"><img src="images/github-mark.png" width="45" height="45" alt="github"/></a></p>
<pre>Copyright (c) 1993-2007 Silicon DSP Corporation
Permission is granted to copy, distribute and/or modify this
document under the terms of the GNU Free Documentation License,
Version 1.2 or any later version published by the Free Software
Foundation; with no Invariant Sections, no Front-Cover Texts, and
no Back-Cover Texts. A copy of the license is included in the
section entitled "GNU Free Documentation License". </pre>
<BR>
<div id="introduction">
<h2>Introduction</h2>
<p style="margin-left:1em;">Silicon DSP Corporation has developed all the C code for a full implementation of a multiple MIMO OFDM Block Diagram Modeling and Simulation Systems  for both Open Loop and Closed Loop MIMO OFDM systems.
The modular architecture uses individual blocks (written in C)  for the implementation of the various stages in modulation and demodulation.
Subroutines ( C code) are also supplied with Include files shared between blocks and subroutines.
See the Block Diagram of a full system <a href="#mimo-ofdm">here</a>.
<p style="margin-left:1em;">The majority of blocks were written in 2006-2007 with major enhancements throughout the years.
<p style="margin-left:1em;">In addition, the Capsim&reg; MIMO OFDM Block Diagram system was extensively used in developing the <a href="https://www.youtube.com/playlist?list=PLqL72R3p_ZYLChzqSDrQGYKl_qvCaFW3U"><img src="images/yt_logo_rgb_light-300x67.png" width="75" height="17" alt="youtube" title="" /></a> tutorials on MIMO OFDM.
<p style="margin-left:1em;">Click  <a href="https://www.youtube.com/playlist?list=PLqL72R3p_ZYLChzqSDrQGYKl_qvCaFW3U">here</a> for the MIMO OFDM Tutorial Videos on <a href="https://www.youtube.com/playlist?list=PLqL72R3p_ZYLChzqSDrQGYKl_qvCaFW3U"><img src="images/yt_logo_rgb_light-300x67.png" width="75" height="17" alt="youtube" title="" /></a>. <!--width="300" height="67" -->
<BR>
<p style="margin-left:1em;">For the development of the fixed point CORDIC Beam Forming MIMO-OFDM the methodology used by Nariankadu D. Hemkumar was used. See the reference below.
<p style="margin-left:1em;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Nariankadu D. Hemkumar, <strong>Efficient VLSI Architectures for Matrix Factorization,</strong> Ph.D. Dissertation, Rice University, April 1994.
<p style="margin-left:1em;">The primary author of the Open-Loop and Closed Loop floating point and fixed point MIMO work was Dr. Sasan Ardalan at Silicon DSP Corporation.  See the OFDM repository at <a href="https://github.com/silicondsp/ofdm-release"><img src="images/github-mark.png" width="45" height="45" alt="github"/></a>for credits on the OFDM blocks and subroutines.
<p style="margin-left:1em;">We highly recommend the following paper for the analysis of the performance of MIMO-OFDM systems:
<p style="margin-left:1em;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Jie Gao, O. C. Ozdural, S. H. Ardalan and Huaping Liu, &quot;<strong>Performance modeling of MIMO OFDM systems via channel analysis</strong>,&quot; in <em>IEEE Transactions on Wireless Communications,</em> vol. 5, no. 9, pp. 2358-2362, September 2006
<p style="margin-left:1em;">Also see the <span style="border-width : 0px;">results of block diagram simulations floating point (LAPACK) versus fixed point CORDIC 2x2 SVD Beam Forming MIMO-OFDM</span> <a href="#results-fxp-floating-point">here</a> <a href="#results-fxp-floating-point"results-fxp-floating-point""><img src="images/noun-links-821764.png" width="30" height="30" alt="link" title="" /></a>in this page.
<p style="margin-left:1em;">Note that blocks are also provided where instead of fixed point CORDIC, the trigonomic functions are computed in floating point. The blocks help validate the fixed point algorithms.
<p style="margin-left:1em;"><strong>Note:</strong> this repository supports the Text Mode Kernel version of Capsim&reg;. 
  The graphical block diagram is from the soon to be released Capsim&reg; Version 7 which uses  Qt&reg; for interactive graphical interface. 
  However, the topology in this Repository are the same. You can use the block names in the screen shot and then use the
  Capsim&reg; command  "to blockname" to go the the block, change parameters and run the simulation.
  There is a lot of benefit to the non graphical mode in portability and flexibility.
  The graphical version also supports the text mode operation.
<p style="margin-left:1em;">An updated link to   Capsim&reg; Version 7  using Qt&reg; will be provided in the Repostory on GitHub. Stay tuned.
<h2 style="margin-left:1em;">Table MIMO OFDM Configurations</h2>
<table style="border: 2px solid #000000; border-collapse: collapse" cellspacing="0" cellpadding="0"  width="734">
  <tr>
    <td width="109" valign="top"><p><strong>Configuration</strong></p></td>
    <td width="40" valign="top"><p><strong>Tx</strong></p></td>
    <td width="42" valign="top"><p><strong>Rx</strong></p></td>
    <td width="75" valign="top"><p><strong>CSI</strong> </p></td>
    <td width="67" valign="top"><p><strong>FFTs</strong></p></td>
    <td width="55" valign="top"><p><strong>SVD</strong></p></td>
    <td width="48" valign="top"><p><strong>QR</strong></p></td>
    <td width="59" valign="top"><p><strong>Rate</strong></p></td>
    <td width="219" valign="top"><p><strong>Application</strong></p></td>
  </tr>
  <tr>
    <td width="109" valign="top"><p>1x1 SISO</p></td>
    <td width="40" valign="top"><p>1</p></td>
    <td width="42" valign="top"><p>1</p></td>
    <td width="75" valign="top"><p>No </p></td>
    <td width="67" valign="top"><p>1</p></td>
    <td width="55" valign="top"><p>No</p></td>
    <td width="48" valign="top"><p>No</p></td>
    <td width="59" valign="top"><p>1x</p></td>
    <td width="219" valign="top"><p>Lowest Data Rate, Lowest Power</p></td>
  </tr>
  <tr>
    <td width="109" valign="top"><p>1x2 MRC</p></td>
    <td width="40" valign="top"><p>1</p></td>
    <td width="42" valign="top"><p>2</p></td>
    <td width="75" valign="top"><p>No</p></td>
    <td width="67" valign="top"><p>2</p></td>
    <td width="55" valign="top"><p>No</p></td>
    <td width="48" valign="top"><p>No</p></td>
    <td width="59" valign="top"><p>1x</p></td>
    <td width="219" valign="top"><p>Reliable Low Rate. Longer range more power.</p></td>
  </tr>
  <tr>
    <td width="109" valign="top"><p>2x2 Open Loop</p></td>
    <td width="40" valign="top"><p>2</p></td>
    <td width="42" valign="top"><p>2</p></td>
    <td width="75" valign="top"><p>No</p></td>
    <td width="67" valign="top"><p>2</p></td>
    <td width="55" valign="top"><p>2x2</p></td>
    <td width="48" valign="top"><p>No</p></td>
    <td width="59" valign="top"><p>2x</p></td>
    <td width="219" valign="top"><p>Medium Data Rate</p></td>
  </tr>
  <tr>
    <td width="109" valign="top"><p>2x2 Beam Forming</p></td>
    <td width="40" valign="top"><p>2</p></td>
    <td width="42" valign="top"><p>2</p></td>
    <td width="75" valign="top"><p>Yes</p></td>
    <td width="67" valign="top"><p>2</p></td>
    <td width="55" valign="top"><p>2x2</p></td>
    <td width="48" valign="top"><p>No</p></td>
    <td width="59" valign="top"><p>2x</p></td>
    <td width="219" valign="top"><p>Medium Date Rate more reliable then Open Loop</p></td>
  </tr>
  <tr>
    <td width="109" valign="top"><p>2x3 Open Loop</p></td>
    <td width="40" valign="top"><p>2</p></td>
    <td width="42" valign="top"><p>3</p></td>
    <td width="75" valign="top"><p>No</p></td>
    <td width="67" valign="top"><p>3</p></td>
    <td width="55" valign="top"><p>2x2</p></td>
    <td width="48" valign="top"><p>Yes</p></td>
    <td width="59" valign="top"><p>2x</p></td>
    <td width="219" valign="top"><p>Reliable Medium Data Rate</p></td>
  </tr>
  <tr>
    <td width="109" valign="top"><p>4x2 Beam Forming</p></td>
    <td width="40" valign="top"><p>4</p></td>
    <td width="42" valign="top"><p>2</p></td>
    <td width="75" valign="top"><p>Yes</p></td>
    <td width="67" valign="top"><p>2</p></td>
    <td width="55" valign="top"><p>2x2</p></td>
    <td width="48" valign="top"><p>No</p></td>
    <td width="59" valign="top"><p>2x</p></td>
    <td width="219" valign="top"><p>High Down link Data Rate, Reliable Up-link, Low Power Video </p></td>
  </tr>
  <tr>
    <td width="109" valign="top"><p>3x4 Open Loop</p></td>
    <td width="40" valign="top"><p>3</p></td>
    <td width="42" valign="top"><p>4</p></td>
    <td width="75" valign="top"><p>No</p></td>
    <td width="67" valign="top"><p>4</p></td>
    <td width="55" valign="top"><p>3x3</p></td>
    <td width="48" valign="top"><p>Yes</p></td>
    <td width="59" valign="top"><p>3x</p></td>
    <td width="219" valign="top"><p>High Data Rate</p></td>
  </tr>
  <tr>
    <td width="109" valign="top"><p>4x4 Beam Forming</p></td>
    <td width="40" valign="top"><p>4</p></td>
    <td width="42" valign="top"><p>4</p></td>
    <td width="75" valign="top"><p>Yes</p></td>
    <td width="67" valign="top"><p>4</p></td>
    <td width="55" valign="top"><p>4x4</p></td>
    <td width="48" valign="top"><p>No</p></td>
    <td width="59" valign="top"><p>4x</p></td>
    <td width="219" valign="top"><p>Very High Data Rate</p></td>
  </tr>
  <tr>
    <td width="109" valign="top"><p>1x4 Beam Forming</p></td>
    <td width="40" valign="top"><p>1</p></td>
    <td width="42" valign="top"><p>4</p></td>
    <td width="75" valign="top"><p>Yes</p></td>
    <td width="67" valign="top"><p>4</p></td>
    <td width="55" valign="top"><p>4x4</p></td>
    <td width="48" valign="top"><p>No</p></td>
    <td width="59" valign="top"><p>1x</p></td>
    <td width="219" valign="top"><p>Very Long  Range</p></td>
  </tr>
</table>
<p style="margin-left:1em;"><p style="margin-left:1em;"><p style="margin-left:1em;">
<p style="margin-left:1em;">
  <BR>
	<img src="images/line.png" width="1000" height="21" alt=""/><BR>
<div id="mimo-ofdm">
<p><img src="images/open_loop_mimo_ofdm_2x2.png" width="1434" height="668" alt=""/></p>
<h2>Capsim® MIMO OFDM 2x2 Open Loop with Channel Modeling and Noise Specification</h2>
<p><img src="images/open_loop_mimo_ofdm_2x3.png" width="1171" height="844" alt=""/></p>
<h2>Capsim&reg; MIMO OFDM 3x2 Open Loop with Channel Modeling and Noise Specificaton</h2>
<p><img src="images/svd-mimo-2x2.png" width="1251" height="873" alt=""/></p>
<h2>Capsim&reg; Closed Loop SVD MIMO OFDM 2x2  with CSI Feedback Channel Modeling and Noise Specificaton</h2>
<p><img src="images/svd_closed_loop_mimo_ofdm.png" width="1353" height="855" alt=""/></p>
<h2>Capsim&reg; Closed Loop SVD MIMO OFDM 4x2  with CSI Feedback Channel Modeling and Noise Specificaton</h2>
<p><BR>
  <img src="images/compare_4x2_versus_2x2_svd_mimo_ofdm.png" width="750" height="744" alt=""/></p>
<h2>Comparison of Received Streams 4x2 SVD MIMO OFDM versus 2x2 SVD MIMO OFDM (Channel 50ns Delay Spread) </h2>
<p><img src="images/mrc-ofdm.png" width="1156" height="817" alt=""/></p>
<h2>Maximum Ratio Combining (MRC)   OFDM (Channel 50ns Delay Spread)</h2>
<p><img src="images/siso_eq.png" width="999" height="802" alt=""/><BR>
  </p>
<h2>SISO (Single Input Single Output)    OFDM (Channel 50ns Delay Spread)</h2>
<div id="results-fxp-floating-point">	
<h1>Results of Block Diagram Simulations Floating Point (LAPACK) versus Fixed Point CORDIC 2x2 SVD Beam Forming MIMO-OFDM</h1>
<h2>Floating Point versus Fixed Point 2x2 Closed Loop MIMO OFDM High SNR</h2>
<p><img src="images/svd_2x2_lapack.png" width="773" height="378" alt=""/></p>
<h3>LAPACK Floating Point Library, 2x2 Beam Forming MIMO OFDM 64 QAM Constellations for Each Stream High SNR</h3>
<p>&nbsp;</p>
<p><img src="images/svd_2x2-fixed-point-cordic.png" width="783" height="380" alt=""/></p>
<h3>CORDIC Fixed Point  2x2 SVD 2x2 Beam Forming MIMO OFDM 64 QAM Constellations for Each Stream  , High SNR</h3>
<h2>Floating Point versus Fixed Point 2x2 Closed Loop MIMO OFDM Medium SNR</h2>
 <p style="margin-left:1em;">A key comparison is the case where channel noise is added. In this case, we expect that the finite precision fixed point CORDIC SVD will enhance noise and degrade performance compared to the floating point LAPACK implementation. This is shown in the fFigures below where noise variance of 1e-5 was added to each receive chain. 
<h1><img src="images/svd-2x2-lapack-noise-added.png" width="798" height="380" alt=""/></h1>
<h3>2x2 Beam Forming MIMO OFDM 64 QAM Constellations for Each Stream LAPACK Floating Point Library, Medium SNR</h3>
<h1><img src="images/svd-2x2-fixed-point-cordic-noise-added.png" width="794" height="378" alt=""/></h1>
<h3>2x2 Beam Forming MIMO OFDM 64 QAM Constellations for Each Stream CORDIC Fixed Point  2x2 SVD , Medium SNR</h3>
	
<h2>More Results on Comparing Floating Point LAPACK versus Fixed Point CORDIC 2x2 SVD</h2>	
<p style="margin-left:1em;">To show that the fixed point CORDIC 2x2 SVD tracks the floating point SVD in a 2x2 MIMO OFDM system we show the plot of the ratio of Singular Values for various carriers (52 for IEEE 802.11a streams) in the  Figure below  with additive noise(variance 1e-5). Note that the ratios track very well over the 52 carriers. The deviation is at the high Singular Value Ratio which corresponds to an ill conditioned channel at that carrier frequency. The enhancement of  roundoff noise is caused at this point and other ill conditioned channel conditions. 	
<p style="margin-left:1em;">	
  <img src="images/SVD_Ratio_Fixed-Point-Vewrsus-Floating-Point-Carriers.png" width="712" height="509" alt=""/>
<h3>Singular Value Ratio: Floating Point versus Fixed Point 2x2 Closed Loop For Each Carrier(52)</h3>		
<div id="tops_list">
</p>
<h1>List of Topologies (Block Diagrams and Hierarchical Blocks and TCL Scripts)</h1>
    <table style="border: 2px solid #000000; border-collapse: collapse" cellspacing="0" cellpadding="0" >
        <tr><th>Item</th><th>Topology Name</th><th>Description</th><th>Author</th><th>Date</th></tr>
        <tr>
            <td>1</td>
            <td> mimo_2x2_eq.t</td>
            <td>MIMO OFDM Open Loop 2 Tx and 2 Rx Antennas</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>2</td>
            <td>mimo_2x3_eq_equal.t </td>
            <td>MIMO OFDM Open Loop 2 Tx and 3 Rx Antennas</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>3</td>
            <td>2x3_mimo_eq_strong_weak.t</td>
            <td>MIMO OFDM Open Loop 2 Tx and 3 Rx Antennas one strong stream and one weak stream due to channel.</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>4</td>
            <td>svdmimo_2x2.t</td>
            <td>SVD Closed Loop MIMO OFDM 2 Tx and 2 Rx Antennas</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>5</td>
            <td>svdmimo_4x2.t</td>
            <td>SVD Closed Loop MIMO OFDM 4 Tx and 2 Rx Antennas</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>6</td>
            <td>intlvrMapperiFFT.t</td>
            <td>Hierarchical Block (HBlock) Interleaver 64 QAM Mapper Pilot Insertion Inverse FFT <a href="#interleaverMapper">Block Diagram Link</a></td>
            <td>Ardalan</td>
            <td>2002</td>
        </tr>
        <tr>
            <td>7</td>
            <td>svdmimo_4x2_float_wk.t</td>
            <td>SVD Closed Loop MIMO OFDM 4 Tx and 2 Rx Antennas CORDIC Floating Point</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>8</td>
            <td>svdmimo_4x2_fxp_wk.t</td>
            <td>SVD Closed Loop MIMO OFDM 4 Tx and 2 Rx Antennas CORDIC Fixed Point (32/16 bit)</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>9</td>
            <td> svd_fxp_2x2_mimo.t</td>
            <td>SVD Closed Loop MIMO OFDM 2 Tx and 2 Rx Antennas CORDIC Fixed Point (32/16 bit)</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>10</td>
            <td>svd_fp_2x2_mimo.t</td>
            <td>SVD Closed Loop MIMO OFDM 4 Tx and 2 Rx Antennas CORDIC Floating Point</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>11</td>
            <td>siso_eq.t</td>
            <td>Single Input Single Output (SISO) OFDM </td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>12</td>
            <td>mimo_mrc.t</td>
            <td>Maximum Ratio Combining (MRC) 2 Tx and 1 Rx Antennas</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>13</td>
            <td>Encoder.t</td>
            <td><span style="margin-left:1em;">Data Field/Scramble/Convolutional Encoder/Puncture</span> HBlock <a href="#Encoder">Block Diagram Link</a></td>
            <td>Ardalan</td>
            <td>2002</td>
        </tr>
        <tr>
            <td>14</td>
            <td>&nbsp; </td>
            <td>&nbsp;</td>
            <td>&nbsp;</td>
            <td>&nbsp;</td>
        </tr>
        <tr>
            <td>18</td>
            <td>&nbsp;</td>
            <td>&nbsp;</td>
            <td>&nbsp;</td>
            <td>&nbsp;</td>
        </tr>
    </table>

<div id="block_list">
<h1>List of Blocks</h1>
   <table style="border: 2px solid #000000; border-collapse: collapse" cellspacing="0" cellpadding="0"  >
        <tr><th width="59">Item</th><th width="166">Block Name</th><th width="307">Description</th><th width="62">Author</th><th width="154">Date</th></tr>
        <tr>
            <td>1</td>
            <td>cxmimoeqzf.s</td>
            <td>Open Loop MIMO Equalizer  Automatically adjust number of channels of  Tx and Rx antennas (Streams)</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>2</td>
            <td>cxmimosvd.s</td>
            <td>Closed Loop SVD MIMO  with LAPACK </td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>3</td>
            <td>cxmimo_2x2_svd.s</td>
            <td>Closed Loop SVD MIMO  CORDIC Fixed Point </td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>4</td>
            <td>cxmimo_2x2_svd_fp.c</td>
            <td>Closed Loop SVD MIMO  CORDIC Floating Point</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>5</td>
            <td>ifftofdm54.s</td>
            <td>inverse FFT 54 Mbps </td>
            <td>Ardalan</td>
            <td>2002</td>
        </tr>
        <tr>
            <td>6</td>
            <td>ifftofdmsvd.s</td>
            <td>inverse FFT 54 Mbps SVD with CSI Support</td>
            <td>Ardalan</td>
            <td>2002/2007</td>
        </tr>
        <tr>
            <td>7</td>
            <td>prcxmat.s</td>
            <td>Print the complex matrix samples. </td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>8</td>
            <td>cxequalizezf..s</td>
            <td>OFDM Frequency Equalizer</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>9</td>
            <td>cxmimoch.s</td>
            <td>MIMO Channel Auto Fan-In and Fan-Out Automatically adjust number of channels per connections for Tx Antennas and Rx antennas.</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>10</td>
            <td>rmcpfx.s</td>
            <td>Remove Cyclic Prefix </td>
            <td>Ardalan</td>
            <td>2002</td>
        </tr>
        <tr>
            <td>11</td>
            <td>evm.s</td>
            <td>Calculate EVM with specifie ideal QAM Map (qam64.dat)</td>
            <td>Ardalan</td>
            <td>2006</td>
        </tr>
        <tr>
            <td>12</td>
            <td>stmat2x4.c </td>
            <td>Convert two streams to 4 streams using orthogonal steering matrix</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>13</td>
            <td>stmat4x2.c </td>
            <td>Convert Four streams to two streams based on transpose of 2x4  using orthogonal steering matrix </td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>14</td>
            <td>fwfft.s</td>
            <td>Forward FFT</td>
            <td>&nbsp;</td>
            <td>&nbsp;</td>
        </tr>
        <tr>
            <td>15</td>
            <td>&nbsp; </td>
            <td>&nbsp; </td>
            <td></td>
            <td></td>
        </tr>
    </table>
<BR>
<div id="subs_table">
    <h1>Table of Subroutines</h1>
    <table style="border: 2px solid #000000; border-collapse: collapse" cellspacing="0" cellpadding="0">
        <tr><th>Item</th><th>Block Name</th><th>Description</th><th>Author</th><th>Date</th></tr>
        <tr>
            <td>1</td>
            <td>Krn_Compute2x2SVDCxMatrix.c </td>
            <td>Compute SVD 2x2 Complex Matrix CORDIC Fixed Point</td>
            <td>Adalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>2</td>
            <td>Krn_Compute2x2SVDCxMatrixFP.c </td>
            <td>Compute SVD 2x2 Complex Matrix CORDIC Floating Point</td>
            <td>Adalang</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>3</td>
            <td>CordicRotate.c </td>
            <td>Fixed Point CORDIC Rotate</td>
            <td>R.Maslennikov, A.Khoryaev</td>
            <td>2003</td>
        </tr>
        <tr>
            <td>4</td>
            <td>CordicArctan.c</td>
            <td>Fixed Point CORDIC Arc Tangent.</td>
            <td>R.Maslennikov, A.Khoryaev</td>
            <td>2003</td>
        </tr>
        <tr>
            <td>5</td>
            <td>krn_dsp.c</td>
            <td>Complex Matrix Operations and Printing</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>6</td>
            <td>krn_lapack.c</td>
            <td>API for Lapack (via CLAPACK) for Eigenvaluue/SVD/Inverse, Complex and Real.</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>7</td>
            <td>MatrixUtils.c</td>
            <td>Matrix Operations Utilities Fixed Point</td>
            <td>Ardalan</td>
            <td>2007</td>
        </tr>
        <tr>
            <td>8</td>
            <td>&nbsp;</td>
            <td>&nbsp;</td>
            <td>&nbsp;</td>
            <td>&nbsp;</td>
        </tr>
    </table>
    <BR><BR>
     <p>
<div id="capsim_ofdm_instructions">
<h1>    Instructions for Running Capsim&reg; MIMO-OFDM Block Diagram Simulation.</h1>
  <p style="margin-left:1em;"><strong>1-</strong> Obtain the Capsim&reg; Text Mode Kernel (CapsimTMK) for Linux  from:
<p style="margin-left:1em;"><a href="https://github.com/silicondsp/capsim-tmk">GitHub Capsim Text Mode  Repository <img src="images/github-mark.png" width="45" height="45" alt="github"/></a>
<p style="margin-left:1em;">CapsimTMK is  distributed with hundreds of  blocks. To simulate OFDM systems the blocks in this repository have to be incorporated into Capsim&reg; including subroutines.
<p style="margin-left:1em;"> This Repository contains the Topologies for MIMO OFDM block diagram modeling inlcuding required  blocks and subroutines.

<p style="margin-left:1em;">Note: Follow the <b>Getting Started Guidelines</b> in the CapsimTMK Repository.
<p style="margin-left:1em;"><strong>2- </strong>Once CapsimTMK is installed just run 'make' in this repository's  Build directory.
<p style="margin-left:1em;"><strong>3- </strong>Then change to the directory 'Topologies' and run:
<p style="margin-left:1em;"><strong></strong>../Build/capsim mimo_2x3_eq_equal.t 
 </strong>
  <p style="margin-left:1em;">The block diagram for the<strong> mimo_2x3_eq_equal.t </strong>topology is shown <a href="#mimo-ofdm">here</a>.
 <p style="margin-left:1em;">Two files will be created:
 <p style="margin-left:1em;"> 
 <pre>
 Welcome to Capsim Text Mode Kernel (CapsimTMK)
(c)1989-2017 Silicon DSP Corporation
This is free software; see the source for copying conditions. There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
http://www.silicondsp.com
Version 6.2
Running topology <span style="margin-left:1em;"> mimo_2x3_eq_equal.t </span>
model name: <span style="margin-left:1em;"> mimo_2x3_eq_equal</span>
...
scatter created file: Scatter0.sct 
scatter created file: Scatter2.sct 
</pre> 
 <BR>
<p style="margin-left:1em;">The two scatter plots showing the 64 QAM constellations can be plotted using the command:	 
<p style="margin-left:1em;"> <strong>source xscatter</strong>
<p style="margin-left:1em;"> <img src="images/xscatter.png" width="1045" height="415" alt=""/>
  
<p style="margin-left:1em;"> The xscatter file is:
<p style="margin-left:1em;"> <strong>java -jar /home/research/SDSP_Github/capsim-tmk/TOOLS/IIPPlot.jar -scatter Scatter0.sct -scatter Scatter1.sct </strong><BR>	<p style="margin-left:1em;">The Java program <strong>IIPPlot.jar</strong> is provided with the CapsimTMK repository. Note the nice capability to plot multiple files..
<p style="margin-left:1em;">For IIPlot Information and Download click <a href="https://www.ccdsp.org/IIPPlot/index.html">here</a>.
<p style="margin-left:1em;">
<p style="margin-left:1em;"> With Linux you can send the plot application to run in the background to put plots side by side when you want to display multiple plots. Then bring them to the forgound and use Control C to exit.
<h2 style="margin-left:1em;">Hierarchical Blocks</h2>
	<div id="Encoder"></div>
<h3 style="margin-left:1em;">Encoder.t<BR>
  <img src="images/Encoder_HBlock.png" width="848" height="374" alt=""/></h3>
	<div id="interleaverMapper"></div>
<h3 style="margin-left:1em;">Hierarchical Block (HBlock) Interleaver 64 QAM Mapper Inverse FFT</h3>
<p style="margin-left:1em;"><img src="images/interleaverMapperPilotHBLOCK.png" width="846" height="378" alt=""/>
<p style="margin-left:1em;">
<p style="margin-left:1em;"><BR>
<div id="linux_tux">
<p><strong>Linux Tux </strong>By <a rel="nofollow" class="external text" href="http://www.isc.tamu.edu/~lewing/">Larry Ewing</a>, <a rel="nofollow" class="external text" href="http://www.home.unix-ag.org/simon/">Simon Budig</a>, <a rel="nofollow" class="external text" href="https://github.com/garrett/Tux">Garrett LeSage</a> - <a rel="nofollow" class="external free" href="https://isc.tamu.edu/~lewing/linux/">https://isc.tamu.edu/~lewing/linux/</a>, <a rel="nofollow" class="external free" href="http://www.home.unix-ag.org/simon/penguin/">http://www.home.unix-ag.org/simon/penguin/</a>, <a rel="nofollow" class="external text" href="https://github.com/garrett/Tux">garrett/Tux</a> on GitHub, <a href="http://creativecommons.org/publicdomain/zero/1.0/deed.en" title="Creative Commons Zero, Public Domain Dedication">CC0</a>, <a href="https://commons.wikimedia.org/w/index.php?curid=753970">Link</a>
  </p>
<p>&nbsp;</p>
<p><BR>
  <p>Capsim® uses LAPACK via CLAPACK.</p>

<p>Anderson, E. and Bai, Z. and Bischof, C. and Blackford, S. and Demmel, J. and Dongarra, J. and Du Croz, J. and Greenbaum, A. and Hammarling, S. and McKenney, A. and Sorensen, D., <strong>LAPACK Users' Guide,</strong>Third Edition,Society for Industrial and Applied Mathematics, Philadelphia, PA, ISBN = 0-89871-447-8, 1999	</p>
  <BR>
  
  <a href="https://www.ccdsp.org/"><img src="sd-logo-tm_sm.png" width="104" height="109" alt="sdsp logo" title="" /></a>
</p>
<p><strong>Silicon DSP Corporation</strong></p>
<p>2002-2025</p>
<p>https://www.ccdsp.org</p>
