<?php
// $Id: themekey.comment.inc,v 1.5.2.4 2010/08/28 08:31:38 mkalkbrenner Exp $

/**
 * @file
 * Provides some comment attributes as ThemeKey properties.
 *
 * @author Markus Kalkbrenner | Cocomore AG
 *   @see http://drupal.org/user/124705
 *
 * @author profix898
 *   @see http://drupal.org/user/35192
 */


/**
 * Implements hook_themekey_properties().
 *
 * Provides additional properties for module ThemeKey:
 * - comment:cid
 *
 * @return
 *   array of themekey properties and mapping functions
 */
function themekey_comment_themekey_properties() {
  // Attributes for properties
  $attributes = array();
  $attributes['comment:cid'] = array(
    'description' => t('Comment: ID - The id of a comment (cid). See !link for your published comments or !link_unpublished for comments awaiting approval',
      array('!link' => l(t('!path', array('!path' => 'admin/content/comment')), 'admin/content/comment'), '!link_unpublished' => l(t('!path', array('!path' => 'admin/content/comment/approval')), 'admin/content/comment/approval'))),
    'validator' => 'themekey_validator_ctype_digit',
    'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
  );

  // Mapping functions
  $maps = array();
  $maps[] = array('src'       => 'comment:cid',
                  'dst'       => 'node:nid',
                  'callback'  => 'themekey_comment_cid2nid');

  return array('attributes' => $attributes, 'maps' => $maps);
}


/**
 * Implements hook_themekey_paths().
 */
function themekey_comment_themekey_paths() {
  $paths = array();
  $paths[] = array('path' => 'comment/reply/#node:nid');
  $paths[] = array('path' => 'comment/reply/#node:nid/#comment:cid');
  $paths[] = array('path' => 'comment/edit/#comment:cid');
  $paths[] = array('path' => 'comment/delete/#comment:cid');

  return $paths;
}


/**
 * ThemeKey mapping function to set a
 * ThemeKey property's value (destination)
 * with the aid of another ThemeKey property (source).
 *
 * src: comment:cid
 * dst: node:nid
 *
 * @param $nid
 *   a comment id
 *
 * @return
 *   a node id
 *   or NULL if no value could be mapped
 */
function themekey_comment_cid2nid($cid) {
  $nid = db_result(db_query('SELECT nid FROM {comments} WHERE cid = %d', $cid));
  return $nid ? $nid : NULL;
}
