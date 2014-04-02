
a.bin:     file format elf32-i386


Disassembly of section .init:

08048294 <_init>:
 8048294:	55                   	push   %ebp
 8048295:	89 e5                	mov    %esp,%ebp
 8048297:	53                   	push   %ebx
 8048298:	83 ec 04             	sub    $0x4,%esp
 804829b:	e8 00 00 00 00       	call   80482a0 <_init+0xc>
 80482a0:	5b                   	pop    %ebx
 80482a1:	81 c3 c0 13 00 00    	add    $0x13c0,%ebx
 80482a7:	8b 93 fc ff ff ff    	mov    -0x4(%ebx),%edx
 80482ad:	85 d2                	test   %edx,%edx
 80482af:	74 05                	je     80482b6 <_init+0x22>
 80482b1:	e8 1e 00 00 00       	call   80482d4 <__gmon_start__@plt>
 80482b6:	e8 f5 00 00 00       	call   80483b0 <frame_dummy>
 80482bb:	e8 e0 01 00 00       	call   80484a0 <__do_global_ctors_aux>
 80482c0:	58                   	pop    %eax
 80482c1:	5b                   	pop    %ebx
 80482c2:	c9                   	leave  
 80482c3:	c3                   	ret    

Disassembly of section .plt:

080482c4 <__gmon_start__@plt-0x10>:
 80482c4:	ff 35 64 96 04 08    	pushl  0x8049664
 80482ca:	ff 25 68 96 04 08    	jmp    *0x8049668
 80482d0:	00 00                	add    %al,(%eax)
	...

080482d4 <__gmon_start__@plt>:
 80482d4:	ff 25 6c 96 04 08    	jmp    *0x804966c
 80482da:	68 00 00 00 00       	push   $0x0
 80482df:	e9 e0 ff ff ff       	jmp    80482c4 <_init+0x30>

080482e4 <__libc_start_main@plt>:
 80482e4:	ff 25 70 96 04 08    	jmp    *0x8049670
 80482ea:	68 08 00 00 00       	push   $0x8
 80482ef:	e9 d0 ff ff ff       	jmp    80482c4 <_init+0x30>

080482f4 <printf@plt>:
 80482f4:	ff 25 74 96 04 08    	jmp    *0x8049674
 80482fa:	68 10 00 00 00       	push   $0x10
 80482ff:	e9 c0 ff ff ff       	jmp    80482c4 <_init+0x30>

Disassembly of section .text:

08048320 <_start>:
 8048320:	31 ed                	xor    %ebp,%ebp
 8048322:	5e                   	pop    %esi
 8048323:	89 e1                	mov    %esp,%ecx
 8048325:	83 e4 f0             	and    $0xfffffff0,%esp
 8048328:	50                   	push   %eax
 8048329:	54                   	push   %esp
 804832a:	52                   	push   %edx
 804832b:	68 30 84 04 08       	push   $0x8048430
 8048330:	68 40 84 04 08       	push   $0x8048440
 8048335:	51                   	push   %ecx
 8048336:	56                   	push   %esi
 8048337:	68 fc 83 04 08       	push   $0x80483fc
 804833c:	e8 a3 ff ff ff       	call   80482e4 <__libc_start_main@plt>
 8048341:	f4                   	hlt    
 8048342:	90                   	nop
 8048343:	90                   	nop
 8048344:	90                   	nop
 8048345:	90                   	nop
 8048346:	90                   	nop
 8048347:	90                   	nop
 8048348:	90                   	nop
 8048349:	90                   	nop
 804834a:	90                   	nop
 804834b:	90                   	nop
 804834c:	90                   	nop
 804834d:	90                   	nop
 804834e:	90                   	nop
 804834f:	90                   	nop

08048350 <__do_global_dtors_aux>:
 8048350:	55                   	push   %ebp
 8048351:	89 e5                	mov    %esp,%ebp
 8048353:	53                   	push   %ebx
 8048354:	8d 64 24 fc          	lea    -0x4(%esp),%esp
 8048358:	80 3d 7c 96 04 08 00 	cmpb   $0x0,0x804967c
 804835f:	75 3e                	jne    804839f <__do_global_dtors_aux+0x4f>
 8048361:	bb 8c 95 04 08       	mov    $0x804958c,%ebx
 8048366:	a1 80 96 04 08       	mov    0x8049680,%eax
 804836b:	81 eb 88 95 04 08    	sub    $0x8049588,%ebx
 8048371:	c1 fb 02             	sar    $0x2,%ebx
 8048374:	83 eb 01             	sub    $0x1,%ebx
 8048377:	39 d8                	cmp    %ebx,%eax
 8048379:	73 1d                	jae    8048398 <__do_global_dtors_aux+0x48>
 804837b:	90                   	nop
 804837c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048380:	83 c0 01             	add    $0x1,%eax
 8048383:	a3 80 96 04 08       	mov    %eax,0x8049680
 8048388:	ff 14 85 88 95 04 08 	call   *0x8049588(,%eax,4)
 804838f:	a1 80 96 04 08       	mov    0x8049680,%eax
 8048394:	39 d8                	cmp    %ebx,%eax
 8048396:	72 e8                	jb     8048380 <__do_global_dtors_aux+0x30>
 8048398:	c6 05 7c 96 04 08 01 	movb   $0x1,0x804967c
 804839f:	8d 64 24 04          	lea    0x4(%esp),%esp
 80483a3:	5b                   	pop    %ebx
 80483a4:	5d                   	pop    %ebp
 80483a5:	c3                   	ret    
 80483a6:	8d 76 00             	lea    0x0(%esi),%esi
 80483a9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

080483b0 <frame_dummy>:
 80483b0:	55                   	push   %ebp
 80483b1:	89 e5                	mov    %esp,%ebp
 80483b3:	8d 64 24 e8          	lea    -0x18(%esp),%esp
 80483b7:	a1 90 95 04 08       	mov    0x8049590,%eax
 80483bc:	85 c0                	test   %eax,%eax
 80483be:	74 12                	je     80483d2 <frame_dummy+0x22>
 80483c0:	b8 00 00 00 00       	mov    $0x0,%eax
 80483c5:	85 c0                	test   %eax,%eax
 80483c7:	74 09                	je     80483d2 <frame_dummy+0x22>
 80483c9:	c7 04 24 90 95 04 08 	movl   $0x8049590,(%esp)
 80483d0:	ff d0                	call   *%eax
 80483d2:	c9                   	leave  
 80483d3:	c3                   	ret    

080483d4 <c_fun>:
 80483d4:	55                   	push   %ebp
 80483d5:	89 e5                	mov    %esp,%ebp
 80483d7:	83 ec 18             	sub    $0x18,%esp
 80483da:	8b 45 08             	mov    0x8(%ebp),%eax
 80483dd:	8b 48 04             	mov    0x4(%eax),%ecx
 80483e0:	8b 45 08             	mov    0x8(%ebp),%eax
 80483e3:	8b 10                	mov    (%eax),%edx
 80483e5:	b8 f4 84 04 08       	mov    $0x80484f4,%eax
 80483ea:	89 4c 24 08          	mov    %ecx,0x8(%esp)
 80483ee:	89 54 24 04          	mov    %edx,0x4(%esp)
 80483f2:	89 04 24             	mov    %eax,(%esp)
 80483f5:	e8 fa fe ff ff       	call   80482f4 <printf@plt>
 80483fa:	c9                   	leave  
 80483fb:	c3                   	ret    

080483fc <main>:
 80483fc:	55                   	push   %ebp
 80483fd:	89 e5                	mov    %esp,%ebp
 80483ff:	83 e4 f0             	and    $0xfffffff0,%esp
 8048402:	e8 19 00 00 00       	call   8048420 <asm_fun>
 8048407:	b8 00 00 00 00       	mov    $0x0,%eax
 804840c:	89 ec                	mov    %ebp,%esp
 804840e:	5d                   	pop    %ebp
 804840f:	c3                   	ret    
 8048410:	90                   	nop
 8048411:	90                   	nop
 8048412:	90                   	nop
 8048413:	90                   	nop
 8048414:	90                   	nop
 8048415:	90                   	nop
 8048416:	90                   	nop
 8048417:	90                   	nop
 8048418:	90                   	nop
 8048419:	90                   	nop
 804841a:	90                   	nop
 804841b:	90                   	nop
 804841c:	90                   	nop
 804841d:	90                   	nop
 804841e:	90                   	nop
 804841f:	90                   	nop

08048420 <asm_fun>:
 8048420:	6a 01                	push   $0x1
 8048422:	6a 02                	push   $0x2
 8048424:	54                   	push   %esp
 8048425:	e8 aa ff ff ff       	call   80483d4 <c_fun>
 804842a:	83 c4 0c             	add    $0xc,%esp
 804842d:	c3                   	ret    
 804842e:	90                   	nop
 804842f:	90                   	nop

08048430 <__libc_csu_fini>:
 8048430:	55                   	push   %ebp
 8048431:	89 e5                	mov    %esp,%ebp
 8048433:	5d                   	pop    %ebp
 8048434:	c3                   	ret    
 8048435:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048439:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048440 <__libc_csu_init>:
 8048440:	55                   	push   %ebp
 8048441:	89 e5                	mov    %esp,%ebp
 8048443:	57                   	push   %edi
 8048444:	56                   	push   %esi
 8048445:	53                   	push   %ebx
 8048446:	e8 4f 00 00 00       	call   804849a <__i686.get_pc_thunk.bx>
 804844b:	81 c3 15 12 00 00    	add    $0x1215,%ebx
 8048451:	83 ec 1c             	sub    $0x1c,%esp
 8048454:	e8 3b fe ff ff       	call   8048294 <_init>
 8048459:	8d bb 20 ff ff ff    	lea    -0xe0(%ebx),%edi
 804845f:	8d 83 20 ff ff ff    	lea    -0xe0(%ebx),%eax
 8048465:	29 c7                	sub    %eax,%edi
 8048467:	c1 ff 02             	sar    $0x2,%edi
 804846a:	85 ff                	test   %edi,%edi
 804846c:	74 24                	je     8048492 <__libc_csu_init+0x52>
 804846e:	31 f6                	xor    %esi,%esi
 8048470:	8b 45 10             	mov    0x10(%ebp),%eax
 8048473:	89 44 24 08          	mov    %eax,0x8(%esp)
 8048477:	8b 45 0c             	mov    0xc(%ebp),%eax
 804847a:	89 44 24 04          	mov    %eax,0x4(%esp)
 804847e:	8b 45 08             	mov    0x8(%ebp),%eax
 8048481:	89 04 24             	mov    %eax,(%esp)
 8048484:	ff 94 b3 20 ff ff ff 	call   *-0xe0(%ebx,%esi,4)
 804848b:	83 c6 01             	add    $0x1,%esi
 804848e:	39 fe                	cmp    %edi,%esi
 8048490:	72 de                	jb     8048470 <__libc_csu_init+0x30>
 8048492:	83 c4 1c             	add    $0x1c,%esp
 8048495:	5b                   	pop    %ebx
 8048496:	5e                   	pop    %esi
 8048497:	5f                   	pop    %edi
 8048498:	5d                   	pop    %ebp
 8048499:	c3                   	ret    

0804849a <__i686.get_pc_thunk.bx>:
 804849a:	8b 1c 24             	mov    (%esp),%ebx
 804849d:	c3                   	ret    
 804849e:	90                   	nop
 804849f:	90                   	nop

080484a0 <__do_global_ctors_aux>:
 80484a0:	55                   	push   %ebp
 80484a1:	89 e5                	mov    %esp,%ebp
 80484a3:	53                   	push   %ebx
 80484a4:	8d 64 24 fc          	lea    -0x4(%esp),%esp
 80484a8:	a1 80 95 04 08       	mov    0x8049580,%eax
 80484ad:	83 f8 ff             	cmp    $0xffffffff,%eax
 80484b0:	74 12                	je     80484c4 <__do_global_ctors_aux+0x24>
 80484b2:	bb 80 95 04 08       	mov    $0x8049580,%ebx
 80484b7:	90                   	nop
 80484b8:	8d 5b fc             	lea    -0x4(%ebx),%ebx
 80484bb:	ff d0                	call   *%eax
 80484bd:	8b 03                	mov    (%ebx),%eax
 80484bf:	83 f8 ff             	cmp    $0xffffffff,%eax
 80484c2:	75 f4                	jne    80484b8 <__do_global_ctors_aux+0x18>
 80484c4:	8d 64 24 04          	lea    0x4(%esp),%esp
 80484c8:	5b                   	pop    %ebx
 80484c9:	5d                   	pop    %ebp
 80484ca:	c3                   	ret    
 80484cb:	90                   	nop

Disassembly of section .fini:

080484cc <_fini>:
 80484cc:	55                   	push   %ebp
 80484cd:	89 e5                	mov    %esp,%ebp
 80484cf:	53                   	push   %ebx
 80484d0:	83 ec 04             	sub    $0x4,%esp
 80484d3:	e8 00 00 00 00       	call   80484d8 <_fini+0xc>
 80484d8:	5b                   	pop    %ebx
 80484d9:	81 c3 88 11 00 00    	add    $0x1188,%ebx
 80484df:	e8 6c fe ff ff       	call   8048350 <__do_global_dtors_aux>
 80484e4:	59                   	pop    %ecx
 80484e5:	5b                   	pop    %ebx
 80484e6:	c9                   	leave  
 80484e7:	c3                   	ret    
